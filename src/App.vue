<script setup lang="ts">
import init from './fib.wasm?init'
import { onMounted, ref } from 'vue';

const duration = ref<number>(0);
const computeNum = ref<number>(0);

// 初始化wasm instance
let instance = null;
let wasmFib: any = null;
onMounted(async () => {
  instance = await init();
  wasmFib = instance.exports.fib
})

const fibRes = ref(0);

// 每次执行20次
const recordPerf = (fn: Function) => {
  return function (...args: any[]) {
    const start = performance.now();
    let result;
    for (let i = 0; i < 20; i++) {
      result =
        fn(...args);
    }
    const dura = performance.now() - start;
    duration.value = dura;
    return result
  }
}
const jsFib = (n: number): number => {
  if (n === 0 || n === 1) {
    return 1;
  }
  return jsFib(n - 1) + jsFib(n - 2);
}

</script>

<template>
  <p>耗时: {{ duration }} ms</p>
  <label>
    输入fib项数
    <input type="number" v-model="computeNum">
  </label>
  <button @click="() => {
    fibRes = recordPerf(jsFib)(computeNum) as any
  }
    ">JS计算fib</button>
  <button @click="() => {
    console.log(recordPerf(wasmFib)(computeNum) as any
    )

    fibRes = recordPerf(wasmFib)(computeNum) as any
  }
    ">wasm计算fib</button>
  <p>计算结果: {{ fibRes }}</p>
</template>

<style scoped></style>



<template> 
    <GggComp />
</template>

<script>
import GggComp from './components/GggComp.vue';
export default {
  name: 'App',
  components: {
    GggComp
  },
}
</script>

<style>
body {
    min-width: 100vw;
    min-height: 100vh;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    background-color: aquamarine;
    transition: all 0.3s ease;
}

.errorbody {
    background-color: rgb(255, 139, 139);
}
</style>




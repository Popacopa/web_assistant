
<template> 
  <button @click="req" class="btn">Click!</button>
</template>

<script>
import axios from 'axios';



export default {
  name: 'GggComp',
  methods : {
    req() {
      /*eslint-disable */
      const response =  axios.post('http://127.0.0.1:5555/api', '1');
    }
  }
}
</script>

<style>

</style>


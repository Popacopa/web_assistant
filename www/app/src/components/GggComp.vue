
<template> 
  <button @click="req" class="btn">{{msg}}</button>
</template>

<script>
import axios from 'axios';

const IP = window.location.hostname;
//let btn = document.querySelector(".btn");
//let body = document.getElementById('body');

export default {
  name: 'GggComp',
  data() {
    return {
      msg: 'OFF',
      d: 0,
    }
  },
  methods : {
    set_data() {
      this.d ? this.d = 0 : this.d = 1;
    },
    async req() {
      try {
        this.set_data();
        const response =  await axios.post(`http://${IP}:8000/api`, String(this.d), {
          headers: {
            'Content-Type': 'application/json',
          }
        });
        this.msg = (this.msg == 'ON' ? 'OFF' : 'ON');

        //btn.classList.remove("errorbtn");
      } catch (error) {
        //btn.classList.add("errorbtn");
        //body.classList.add("errorbtn");
        console.error('Error during request:', error.response);
        this.msg = 'Error';
        return;
      }
    }
  }
}
</script>

<style>
.btn {
    font-family: 'Arial', Courier, monospace;
    display: inline-block;
    padding: 10px 20px;
    margin: 5px;
    font-size: 16px;
    background-color: #45a83f;
    color: white;
    text-decoration: none;
    border-radius: 5px;
    border: none;
    cursor: pointer;
    transition: all 0.3s ease;
}

.btn:hover {
    background-color: rgb(106, 141, 106);
}

.errorbtn {
    background-color: rgb(254, 66, 66);
}

.errorbtn:hover {
    background-color: rgb(255, 0, 0);
}

</style>


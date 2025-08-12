import { createApp } from 'vue'
import App from './App.vue'
import GggComp from './components/GggComp.vue';



const app = createApp(App);
app.component('GggComp', GggComp);  // Now it can be used anywhere
app.mount('#app');
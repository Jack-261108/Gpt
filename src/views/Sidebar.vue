<template>
 <div v-show="!isShow" @click="isShow = true" class="closeaside">
      >>
    </div>
      <div class="aside" v-show="isShow">
        <div class="asidebar">
          <button>+ new chat</button>
          <button @click="isShow = false">
            &lt;&lt;
          </button>
        </div>
        <div class="history">

        </div>
        <div class="asidebarfooter"></div>
      </div>
</template>
<script setup>
import {ref} from 'vue'
const isShow = ref(true)
</script>
<style scoped>
.closeaside {
  text-align: center;
  color: #fff;
  margin: 10px 10px;
  width: 30px;
  height: 30px;
  line-height: 30px;
  /* padding: 10px 0; */
  border-radius: 5px;
}

.closeaside:hover {
  background-color: rgb(68, 70, 84);
}

.asidebar {
  padding: 10px 10px;
  display: flex;
  justify-content: space-between;
  height: 80px;
}

.history {
  flex: 1;
  border-bottom: 1px solid hsla(0, 0%, 100%, .2);
}

.asidebar :nth-child(1) {
  padding: 0 20px;
  flex: 1;
}

.asidebar button {
  border-radius: 5px;
  border: 1px solid hsla(0, 0%, 100%, .2);
  color: #fff;
  background-color: transparent;
  height: 30px;
}

.asidebar :nth-child(2) {
  width: 30px;
  margin-left: 10px;
}

.asidebarfooter {
  height: 80px;
}
.aside {
  display: flex;
  flex-direction: column;
  background-color: rgb(32, 33, 35);
  width: 250px;
  min-height: 100vh;
  transition: all 1s;
}
</style>
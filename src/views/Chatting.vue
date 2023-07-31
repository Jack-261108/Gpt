<template>
  <div class="app">
    <Sidebar></Sidebar>
    <div class="wrapper">
      <div class="body">
        <el-header class="header">gpt3</el-header>
        <div class="main" ref="main">
          <ul>
            <li v-for="m in list" :key="m">
              <div class="messageitem">
                <img v-if="m.type === 1" src="../assets/imgs/1234.jpg" class="avter">
                <img v-else src="../assets/imgs/img.png" class="avter">
                <div class="message" v-html="m.message">
                </div>
              </div>
            </li>
          </ul>
        </div>
        <el-footer class="footer">
          <div class="send">
            <input placeholder="Send a message" class="textarea" v-model="inputvalue" ref="message">
            <button :class="{ 'active': !isButtonEnabled, 'inActive': isButtonEnabled }" :disabled="isButtonEnabled"
              @click="sendMessage">>
            </button>
          </div>
          <div class="copyright">Free Research Preview. ChatGPT may produce inaccurate information about people, places,
            or facts. ChatGPT
            July 20 Version
          </div>
        </el-footer>
      </div>
    </div>
  </div>
</template>
<script setup>
// import {, ref } from 'vue';
import { generateUUid } from '../utils/util'
import md from '../utils/markdown'
import { onMounted, onUpdated, ref, computed } from 'vue';
import { ElMessage } from 'element-plus'
import Sidebar from './Sidebar.vue';
const inputvalue = ref("")
const isButtonEnabled = computed(() => {
  return inputvalue.value === ''
})
const isFirst = ref(true)
const socket = ref(null)
const list = ref([])
const message = ref(null)
const isActive = ref(false)
const main = ref(null)
const sendMessage = () => {
  list.value.push({
    message: inputvalue.value,
    type: 1
  })
  socket.value.send(inputvalue.value)
  inputvalue.value = '';
}
onUpdated(() => {
  main.value.scrollTop = main.value.scrollHeight
})
onMounted(() => {
  console.log()
  let text = '';
  let uid = window.localStorage.getItem("uid");
  if (uid == null || uid === '' || uid === 'null') {
    uid = generateUUid();
  }
  // 设置本地存储
  window.localStorage.setItem("uid", uid);
  if (typeof (WebSocket) == "undefined") {
    console.log("您的浏览器不支持WebSocket");
  } else {
    console.log("您的浏览器支持WebSocket");
    //实现化WebSocket对象
    //指定要连接的服务器地址与端口建立连接
    //注意ws、wss使用不同的端口。我使用自签名的证书测试，
    //无法使用wss，浏览器打开WebSocket时报错
    //ws对应http、wss对应https。
    socket.value = new WebSocket("ws://localhost:8000/websocket/" + uid);
    //连接打开事件
    socket.value.onopen = function () {
      isActive.value = true
      ElMessage({
        message: '连接成功',
        type: 'success',
      })
    };
    //收到消息事件
    socket.value.onmessage = function (msg) {
      if (msg.data === "[DONE]") {
        isFirst.value = true
        text = '';
        return;
      }
      let json_data = JSON.parse(msg.data)
      if (json_data.content == null || json_data.content === 'null') {
        text = '';
        return;
      }
      text = text + json_data.content;
      if (isFirst.value === true) {
        list.value.push({ message: md.render(text), type: 0 })
        isFirst.value = false
      } else {
        list.value.pop()
        list.value.push({ message: md.render(text), type: 0 })
      }

    };
    //连接关闭事件
    socket.value.onclose = function () {
      isActive.value = false
      ElMessage({
        message: 'socket 连接已关闭',
        type: 'warn',
      })
    };
    //发生了错误事件
    socket.value.onerror = function () {
      ElMessage({
        message: '服务异常请重试并联系开发者！',
        type: 'error',
      })
    }
    //窗口关闭时，关闭连接
    window.unload = function () {
      isActive.value = false
      socket.close();
    };
  }
  // 回车事件
  console.log(message.value)
  message.value.onkeydown = () => {
    if (window.event.keyCode === 13) {
      console.log("success")
      sendMessage()
    }
  };
})
</script>
<style scoped>
.main::-webkit-scrollbar {
  width: 0;
  /* height: 0; */
  background-color: transparent;
}

.main ul li {
  margin: 10px 0;
  width: 100%;
  height: fit-content;
  /* background-color: brown; */
}

.message {
  padding: 10px 5px;
  max-width: 80%;
  height: fit-content;
  margin-left: 5px;
  /* background-color: gray; */
  border-radius: 3px;
  color: #fff;
}

.avter {
  width: 30px;
  height: 30px;
}

.messageitem {
  border-radius: 10px;
  background-color: rgb(68, 70, 84);
  max-width: 100%;
  display: flex;
}

.messageitem img {
  border-radius: 3px;
  margin: 5px 5px;
}

.header {
  line-height: 100%;
  text-align: center;
  background-color: blueviolet;
}

.app {
  display: flex;
}


.wrapper {
  /* flex: 1; */
  width: 800px;
  margin: 0 auto;
  height: 100vh;
}

.send {
  align-items: center;
  display: flex;
  border-radius: 5px;
  background-color: rgb(68, 70, 84);
  padding: 10px 5px;
  /* box-shadow: 1px 1px 20px 0px black; */
}

.active {
  width: 30px;
  height: 30px;
  color: #fff;
  font-size: 16px;
  border: none;
  border-radius: 5px;
  background-color: rgb(25, 195, 125);
  transition: all 0.5s;
}

.inActive {
  width: 30px;
  height: 30px;
  color: rgb(91, 92, 107);
  font-size: 16px;
  border: none;
  border-radius: 5px;
  background-color: transparent;
  transition: all 0.5s;
}

.textarea {
  color: #fff;
  width: 100%;
  border: 1px solid transparent;
  outline: none;
  appearance: none;
  height: 18px;
  max-height: 200px;
  overflow-y: hidden;
  background-color: rgb(68, 70, 84);
}

.body {
  height: 100%;
  display: flex;
  flex-direction: column;
}

.main {
  padding: 0 0;
  flex: 1;
  margin-top: 10px;
  border-radius: 5px;
  overflow: auto;
}

.copyright {
  margin-top: 5px;
}

.footer {
  height: 80px;
  color: #fff;
  text-align: center;
  margin-top: 5px;
  /* background-color: #efefef; */
}
</style>
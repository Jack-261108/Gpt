<script setup>
import {generateUUid} from '../utils/util'
import md from '../utils/markdown'
import {onMounted, onUpdated, ref} from 'vue';
import {ElMessage} from 'element-plus'

const isFirst = ref(true)
const msglist = ref(null)
const socket = ref(null)
const list = ref([])
const message = ref(null)
const isActive = ref(false)
const inputvalue=ref("")
const sendMessage = () => {
  list.value.push({
    message: inputvalue.value,
    type: 1
  })
  socket.value.send(inputvalue.value)
  inputvalue.value=''
}
onUpdated(() => {
  console.log("aaaa")
  msglist.value.scrollTop = msglist.value.scrollHeight
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
        list.value.push({message: md.render(text), type: 0})
        isFirst.value = false
      } else {
        list.value.pop()
        list.value.push({message: md.render(text), type: 0})
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
<template>
  <div class="container">
    <div class="wrapper">
      <div class="header">gpt3.5 <span :class="{ active: isActive, inactive: !isActive }"></span></div>
      <div class="chatlist" ref="msglist">
        <ul>
          <li v-for="m in list" :key="m">
            <div class="messageitem">
              <img v-if="m.type===1" src="../assets/imgs/1234.jpg" class="avter">
              <img v-else src="../assets/imgs/img.png" class="avter">
              <div class="message" v-html="m.message">
              </div>
            </div>
          </li>
        </ul>
      </div>
      <div class="footer">
        <div id="send">
          <input placeholder="input your message" ref="message" v-model="inputvalue">
          <button @click="sendMessage">send</button>
        </div>
        <div id="copyright">
          Free Research Preview. ChatGPT may produce inaccurate information about people, places, or facts.
          ChatGPT July 20 Version
        </div>
      </div>
    </div>
  </div>
</template>
<style scoped>

.footer {
  height: 80px;
}

.wrapper {
  flex-direction: column;
  display: flex;
  height: 100vh;
  width: 1000px;
  margin: 0 auto;
  background-color: rgb(52, 53, 65);
}

.chatlist {
  padding: 0 10px;
  /* background-color: pink; */
  /* height: 500px; */
  flex: 1;
  overflow: auto;
  background-color: rgb(52, 53, 65);
}

.chatlist::-webkit-scrollbar {
  width: 0;
  height: 0;
  background-color: transparent;
}

#send {
  text-align: center;
  padding-bottom: 5px;
  width: 60%;
  align-items: center;
  display: flex;
  margin: 10px auto 0;
}

.active {
  line-height: 60px;
  margin-top: 5px;
  border-radius: 10px;
  display: inline-block;
  width: 20px;
  height: 20px;
  background-color: #08ec45;
}

.inactive {
  line-height: 60px;
  margin-top: 5px;
  border-radius: 10px;
  display: inline-block;
  width: 20px;
  height: 20px;
  background-color: #686d76;
}

#send input {
  outline: none;
  padding: 0 10px;
  width: 80%;
  height: 40px;
  border-radius: 5px;
  border: 1px solid black;
}

#send button {
  margin-left: 10px;
  padding: 10px 10px;
  height: fit-content;
  width: 60px;
}

.chatlist ul li {
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
  vertical-align: middle;
  font-size: 20px;
  line-height: 60px;
  text-align: center;
  background-color: rgb(52, 53, 65);
  height: 60px;
  margin: 0 auto;
  color: #fff;
}

#copyright {
  text-align: center;
  max-width: 80%;
  color: #fff;
  padding-left: 80px;
}
</style>

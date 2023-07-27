<script setup>
import MarkdownIt from 'markdown-it';
import hljs from 'highlight.js';
import 'highlight.js/styles/default.css';
const md = new MarkdownIt();
const isFirst = ref(true)
const msglist = ref(null)
import { computed, onMounted, onUpdated, ref } from 'vue';
import { ElMessage } from 'element-plus'
const socket = ref(null)
const list = ref(["hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？hello,我有什么可以帮助你的？", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello"])

const message = ref(null)

const sendMessage = () => {
  const msg = message.value.value
  list.value.push(msg)
  socket.value.send(msg)
  message.value.value = ''
}
const uuid = () => {
  var s = [];
  var hexDigits = "0123456789abcdef";
  for (var i = 0; i < 36; i++) {
    s[i] = hexDigits.substr(Math.floor(Math.random() * 0x10), 1);
  }
  s[14] = "4"; // bits 12-15 of the time_hi_and_version field to 0010
  s[19] = hexDigits.substr((s[19] & 0x3) | 0x8, 1); // bits 6-7 of the clock_seq_hi_and_reserved to 01
  s[8] = s[13] = s[18] = s[23] = "-";

  var uuid = s.join("");
  return uuid;
}
onUpdated(() => {
  msglist.value.scrollTop = msglist.value.scrollHeight
})
onMounted(() => {
  let uuid_str = '';
  let text = '';
  let chat = document.getElementById("chat");
  let uid = window.localStorage.getItem("uid");
  if (uid == null || uid == '' || uid == 'null') {
    uid = uuid();
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
      ElMessage({
        message: 'socket 已打开',
        type: 'success',
      })
    };
    //收到消息事件
    socket.value.onmessage = function (msg) {
      if (msg.data == "[DONE]") {
        isFirst.value = true
        text = '';
        return;
      }
      let json_data = JSON.parse(msg.data)
      if (json_data.content == null || json_data.content == 'null') {
        text = '';
        return;
      }
      text = text + json_data.content;
      if (isFirst.value == true) {
        list.value.push((md.render(text)))
        isFirst.value = false
      } else {
        list.value.pop()
        list.value.push((md.render(text)))
      }

    };
    //连接关闭事件
    socket.value.onclose = function () {
      ElMessage({
        message: 'socket 连接已关闭',
        type: 'error',
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
      socket.close();
    };
  }
  // 回车事件
  // messageElement.onkeydown = function () {
  //   if (window.event.keyCode === 13) {
  //     if (!messageElement.value) {
  //       return;
  //     }
  //     uuid_str = uuid();
  //     socket.send(messageElement.value);
  //     //新增问题框
  //     chat.innerHTML += '<tr><td style="height: 50px;">' + messageElement.value + '</td></tr>';
  //     messageElement.value = null
  //     //新增答案框
  //     chat.innerHTML += '<tr><td><article id="' + uuid_str + '" class="markdown-body"></article></td></tr>';
  //   }
  // };
})
</script>
<template>
  <div class="container">
    <div class="wrapper">
      <div class="header">gpt3.5</div>
      <div class="chatlist" ref="msglist">
        <ul>
          <li v-for="m in list" :key="m">
            <div class="messageitem">
              <img src="../assets/imgs/1234.jpg" class="avter">
              <div class="message">
                <article v-html='m'></article>
              </div>
            </div>
          </li>
        </ul>
      </div>
      <div id="send">
        <input placeholder="input your message" ref="message">
        <button @click="sendMessage">send</button>
      </div>
      <div id="copyright">
        Free Research Preview. ChatGPT may produce inaccurate information about people, places, or facts.
        ChatGPT July 20 Version
      </div>
    </div>
  </div>
</template>
<style scoped>
.continer {
  max-height: 100%;
}

.wrapper {
  width: 1000px;
  margin: 0 auto;
  background-color: rgb(52, 53, 65);
}

.chatlist {
  overflow-y: hidden;
  padding: 0 10px;
  /* background-color: pink; */
  height: 500px;
  overflow: auto;
  background-color: rgb(52, 53, 65);
}

.chatlist::-webkit-scrollbar {
  width: 0px;
  height: 0px;
  background-color: transparent;
}

#send {
  text-align: center;
  padding-bottom: 5px;
  width: 60%;
  align-items: center;
  margin: 0 auto;
  display: flex;
  margin-top: 10px;
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
  margin-left: 10px;
  margin: 10px 0px;
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

<template>
    <el-footer class="footer">
          <div class="send">
            <input placeholder="Send a message" class="textarea" v-model="inputvalue" ref="message">
            <button :class="{ 'active': !isButtonEnabled, 'inActive': isButtonEnabled }"
                    :disabled="isButtonEnabled" @click="sendMessage">>
            </button>
          </div>
          <div class="copyright">Free Research Preview. ChatGPT may produce inaccurate information about people, places,
            or facts. ChatGPT
            July 20 Version
          </div>
        </el-footer>
</template>
<script setup>
import {computed,ref} from 'vue'
const inputvalue=ref("")

const isButtonEnabled = computed(() => {
  return inputvalue.value === ''
})
</script>
<style scoped>
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
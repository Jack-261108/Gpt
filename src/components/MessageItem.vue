<template>
    <div class="messageitem" v-for="m in messageList" :key=m.id>
        <img src="C:\Users\张欢\Desktop\1234.jpg" class="avter">
        <div class="message">
            {{ m.content }}
        </div>
    </div>
</template>
<script setup>
import { ref } from 'vue'
const messageList = ref([])
</script>
<style scoped>
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

.avter {
    width: 30px;
    height: 30px;
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
</style>
import { defineStore } from "pinia";
import { computed, ref } from 'vue'
export const messageStore = defineStore('message', () => {
    const messageList = ref([])
    const putMsg = async (msg) => {
        messageList.value.push(msg)
    }
    const deleteMsg = async (msg) => {
        messageList.value.splice(msg)
    }
    const getAllmsg = computed(() => {
        return messageList.value
    })
    return { getAllmsg, putMsg, deleteMsg }
})
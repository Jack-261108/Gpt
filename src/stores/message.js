import { defineStore } from "pinia";
import { computed, ref } from 'vue'
export const messageStore = defineStore('message', () => {
    const isFirst = ref(false)
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
    const streamMsg = (msg) => {
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

    }
    return { getAllmsg, putMsg, deleteMsg, streamMsg }
})
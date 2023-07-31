import {createRouter, createWebHistory} from 'vue-router'
import HomeView from '../views/HomeView.vue'
import Chatting from '../views/Chatting.vue'
import send from '../views/send.vue'
import sidebar from '../views/sidebar.vue'
const router = createRouter({
    history: createWebHistory(import.meta.env.BASE_URL),
    routes: [
        {
            path: '/',
            name: 'home',
            component: HomeView
        }, {
            path: '/test',
            component: Chatting
        },{
            path: '/send',
            component: send
        },{
            path: '/side',
            component: sidebar
        }
    ]
})

export default router

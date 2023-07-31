import MarkdownIt from 'markdown-it';
import hljs from 'highlight.js';
import 'highlight.js/styles/default.css';
 const md = new MarkdownIt({
    highlight: function (str, lang) {
      const template = '<pre class="hhhh" style="background: black;color: #fff;border-radius: 10px;padding: 15px 15px;margin: 10px 0"><code>{text}</code></pre>'
      if (lang && hljs.getLanguage(lang)) {
        try {
          return template.replace("{text}", hljs.highlight(lang, str, true).value)
        } catch (__) { }
      }
      return template.replace("{text}", md.utils.escapeHtml(str))
    },
  });
  export default md;
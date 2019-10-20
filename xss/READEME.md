## XSS
### 正则

* \g 全局匹配
### HTML Context
* Inside Tag
* Outside Tag
#### Inside Tag

#### Outside Tag 
* re 匹配某个tag
  * ```<svg ```
  * ```<dev```  if fails,```<[a-z]+```
  * ```x<dev```  if fails,```^<[a-z]+```
  * ```<dEv``` if fails,```<[a-zA-Z]+```
  * ```<d3v``` if fails,```<[a-zA-Z0-9]+```
  * ```<d|3v``` if fails,```<[.+``` 
* payload 方案#1

### 编码
####URL 编码
* 只有字母和数字[0-9a-zA-Z]、一些特殊符号"$-_.+!*'(),"[不包括双引号]、以及某些保留字，才可以不经过编码直接用于URL。
* ```encodeURI()```  ```decodeURI()```
  * 对整个URL编码，对" ' ; / ? : @ & = + $ , # "不进行编码，输出符号的UTF-8形式，并在每个字节前加%
* ```encodeURIComponent()``` ```decodeURIComponent()```
  * 由于 encodeURI 不对特殊字符编码，若查询关键字出现它们，则使用encodeURIComponent() 进行部分编码
* reference：
  * [关于URL编码](http://www.ruanyifeng.com/blog/2010/02/url_encoding.html)
  * [字符编码笔记：ASCII，Unicode 和 UTF-8](http://www.ruanyifeng.com/blog/2007/10/ascii_unicode_and_utf-8.html)
####HTML 编码
* HTML一些被占用或具有特殊功能的符号使用特殊方法标记以便展示
* HTML 实体编码
  * &entity_name 或  &entity_number
    * < &nbsp;&nbsp;```&lt;``` 或 ```&#60;```
    * 空格 &nbsp;&nbsp;```&nbsp;``` 
  * 对大小写敏感
* reference
  * [html实体集](https://www.w3school.com.cn/html/html_entities.asp)
####JS 编码
* JavaScript 中某些字符有特殊用途，若想使用其原义，则使用反斜杠对它们进行转义。
* ```\& \' \" \& \\ \n \r \t```
###　XSS 攻击
#### 定义
* 实质是 HTML 与 JavaScript 代码的注入
* 若用户输入中某个参数的全部或其中一部分原封不动在源代码中显示，我们则可以认为这个参数存在XSS漏洞
#### 以下内容都不可信
* UCC（User-created Content）
* 来自第三方的链接
* URL 参数
* POST 参数
* Referer (来自不可信的来源)
* Cookie (来自其它子域注入)
#### 注入方法
* html 内嵌文本，以 script 标签形成注入
  
  * 无任何过滤措施   
    *   ```<input type="text" value="<%= getParameter("keyword") %>">```
    *    ```keyword="><script> alert('XSS!'); </script>```

  * ```s = s.replace(/"/g, '\\"');```将引号转义为真正引号
    * ```\"``` 使结果为 ```\\\"``` 真正转义的是 反斜杠而非双引号
  *  ```s = JSON.stringify(s);``` JSON.stringify只转义引号
     *  ```</script><script>alert(1);//``` 若不加 // 注释，js找不到引号对应的另一个引号，则不会渲染只会报错？
* 在内联的 JavaScript 中，拼接的数据突破原本的限制
* 标签属性中，加入 引号 ，从而注入其它 attribute 或 tag
* 在标签的 href、src 等属性中，包含 JavaScript: 等可执行代码
* 在 onload 、onerror 、onclick 等事件中注入不受控制的代码
* 在 style 属性和标签中，包含类似 background-image:url("javascript:..."); 的代码（新版本浏览器可以防范）
* 在 style 属性和标签中，包含类似 expression(...) 的CSS表达式代码（新版本浏览器可以防范）

#### 反射型 XSS
* 攻击者构造特殊 URL 分享给用户，用户打开后浏览器解析执行，恶意代码或窃取用户数据并发送到攻击者域，或冒充用户身份调用网站接口执行攻击者指定的操作
#### 持久性 XSS
* 攻击者将恶意代码提交到目标网站数据库中
#### DOM型 XSS
* 取出和执行恶意代码由浏览器端完成，属于前端JavaScript自身的漏洞。前两种属于服务端的漏洞
### XSS防御







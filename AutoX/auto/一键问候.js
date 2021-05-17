//设置指定QQ号的数组, QQ号必须为好友.
var uinArry = [
    "3080396859",
    "2051776471",
    "1968356437",
    "2389593059",
    "1546163940",
    "1317284538",
    "2957670531",
    "2231047987",
    "1444846271",
    "1778251804"
]

//给每个QQ号发送你好啊.
for (let i = 0; i < uinArry.length; i++) {
    app.startActivity({
        data:"mqqwpa://im/chat?chat_type=wpa&uin="+uinArry[i],
    });
    text("发送").waitFor();
    sleep(500);
    id("input").setText("小问题");
    sleep(500);
    while(!click("发送"));
    sleep(500);
}
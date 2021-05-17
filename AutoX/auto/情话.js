"auto";
console.show();
t = "";
while (true) {
    var t=TEXT();
    setText(t);
    sleep(500);
    while (!click("发送"));
    //sleep(500);
    //sleep(2*1000);
}


function TEXT() {
    var url = "https://api.lovelive.tools/api/sweetnothings";
    var txt = http.get(url).body.string(); 
    return txt;
};
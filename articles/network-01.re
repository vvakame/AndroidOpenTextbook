= ネットワークプログラミング

この章ではHTTPサーバからファイルを取得するさまざまな方法を通してネットワーク通信の仕組みを学びます。
Webサーバーと連携して最新のデータを取得したり、他のプラットフォームと同期するためにデータを送信したりする際にネットワークの知識が必要になります。

== ネットワークってなんだろう

ネットワーク通信とは２つ以上のコンピュータでデータのやりとりをすることです。
ネットワークを話題にするときには、コンピュータのことをホストと呼びます。コンピュータ＝ホストと思って頂いて構いません。

たとえばAndroidでインターネットブラウザを使ってhttp://tomorrowkey.jp というウェブページを開いたとしましょう。
この時、Androidの携帯電話とインターネットの向こう側にあるホストとデータのやりとりをします（@<img>{image-of-network}）。

//image[image-of-network][AndroidでWebページを表示するとき]{
//}

ウェブページを要求することをリクエストといいます。またそのリクエストに対する返信をレスポンスといいます。
リクエストをしたら必ずレスポンスが返ってきます。
ネットワーク通信では、クライアントからサーバーにリクエストを送り、サーバからレスポンスを取得することをセットで考えます。

他のホストからのリクエストを待ち、データを提供するホストをサーバーといいます。
それに対してリクエストを送る側のホストをクライアントといいます。

== IPアドレス

インターネットにはたくさんのホストが繋がっています。
ネットワーク通信を行う際は、どのホストと通信するか指定する必要があります。
各ホストは異なる番号を持っていて、それをIPアドレス@<fn>{about-IPv6}といいます。
IPアドレスは次のように4つの数字をドットで区切った形式で表します（@<list>{ipaddress}）。

//footnote[about-IPv6][ここで説明しているのはIPv4と呼ばれるものです。容量を大きくしたIPv6というものもあります。詳しくは"IPアドレス枯渇問題"というワードで検索してみてください]

//list[ipaddress][IPアドレス]{
192.168.12.10
//}

みなさんが使っているコンピュータにもIPアドレスがあります。
あなたのコンピュータがどんなIPアドレスを使っているのか確認してみましょう。

IPアドレスを調べるには次のコマンドを実行します。
使用しているOSがMacやLinuxなどのUnix系の場合は次のコマンドをターミナルで実行します（@<list>{ifconfig}）。
//list[ifconfig][IPアドレスを調べるコマンド(OSX, Linuxなど)]{
> ifconfig
//}

使用しているOSがWindowsの場合は次のコマンドをコマンドプロンプトで実行します（@<list>{ipconfig}）。
//list[ipconfig][IPアドレスを調べるコマンド(Windows)]{
> ipconfig
//}

== 名前解決

前節でIPアドレスについて説明しましたが、1つ疑問が湧いてきました。
ブラウザでWebサーバにアクセスするときにはIPアドレスを指定せずにファイルのやりとりをしました。
ネットワーク通信する際にはIPアドレスの指定が必要と説明しましたが、ブラウザはどのようにIPアドレスを知ったのでしょうか。

それを実現するのが名前解決と呼ばれる技術です。DNS（Domain Name System）とも呼ばれます。
ネットワーク通信を行う際はIPアドレスを指定しなければなりませんが、実際その値は覚えにくく、人間に分かりやすいものではありません。

名前解決とは人間に分かりやすい文字列の"ホスト名"から"IPアドレス"に変換する処理のことをいいます。
また、その逆の変換も可能なので、名前解決では"ホスト名"とIPアドレスを相互に変換することができます。

さきほどブラウザでWebページにアクセスした時を例に具体的な説明をします。
ブラウザでは"http://tomorrowkey.jp/" という値を入力しました。これの"tomorrowkey.jp"という部分がホスト名です。
ブラウザはこの"ホスト名"からIPアドレスをDNSサーバに問い合わせます。
DNSサーバはこの"tomorrowkey.jp" という値から"49.212.164.150" というIPアドレスを返します。
これでIPアドレスが分かったので、ブラウザはサーバと通信を始めるのです。

また、この名前解決はターミナル/コマンドプロンプトで実行することもできます（@<list>{nslookup}）。
//list[nslookup][名前解決のコマンド]{
nslookup "ホスト名"
//}

実行すると次のようにサーバのIPアドレスを取得できます（@<list>{result-of-nslookup}）。
//list[result-of-nslookup][nslookupの実行結果]{
$ nslookup tomorrowkey.jp
Server:   220.159.212.200
Address:  220.159.212.200#53

Non-authoritative answer:
Name: tomorrowkey.jp
Address: 49.212.164.150
//}

名前とIPアドレスは同じものなので、さきほど取得したIPアドレスをブラウザに入力した場合も"http://tomorrowkey.jp/"と入力した場合と同じページが表示されます。

== プロトコル
名前解決を使ってIPアドレスを取得でき、サーバを特定しました。
2つのホストが結ばれたとき、どのような内容のデータをやりとりするのでしょうか。

データをどのような順番で送るかという"方法"をあらかじめ決めておかなければ、
サーバからクライアントに送られてきたデータにどういう意味があるのか、クライアントは知ることができません。
その"方法"の総称をプロトコルといいます。

さきほど説明したDNSもプロトコルの一種です。
DNSは"名前をDNSサーバに渡すことでIPアドレスを返す"という仕組みがあらかじめ決められています。

Webサーバーからページを取得するときに使われるプロトコルをHTTPといいます。
ホストに対して特定のページがほしいとリクエストを送ると、そのページがレスポンスとして返されます。

ブラウザで"http://tomorrowkey.jp/" にアクセスした場合を例にとって、具体的な値を説明しましょう。
ブラウザはサーバに対して次のようなリクエストを送っています（@<list>{http-request}）。

//list[http-request][HTTPリクエスト]{
GET / HTTP/1.0
User-Agent: Mozilla/5.0 (Linux; Android 4.3; Build/LPV79)
 AppleWebKit/537.36 (KHTML, like Gecko) 
 Chrome/36.0.1985.94 Mobile Safari/537.36
Host: tomorrowkey.jp
//}

1行目にはHTTPアクセスする概要を指定します。

まず最初のパラメータで、アクセスの種類を指定します。
上記リクエストでは"GET"となっていますが、これはファイルの取得を意味します。他にPOST、PUTやDELETEなどがあります。
スペースで区切って、1行目2つ目のパラメータとして取得するファイルの名前を指定します。
"/"と書かれていますが、Webサーバでは"/"とリクエストされたものはたいてい"index.html"と解釈されます。
さらにスペースで区切った後ろにHTTPのバージョンを書きます。

2行目以降はヘッダーと呼ばれるリクエストする際の付属的な情報を書きます。
User-Agentにはどのようなソフトウェアを使ってアクセスしているかを指定します。
Hostはアクセスするホストの名前を指定します。http://tomorrowkey.jpにアクセスするのでtomorrowkey.jpがホスト名になります。

続いてレスポンスを見てみましょう(@<list>{http-response})

//list[http-response][telnetを使ったHTTP通信のレスポンス]{
HTTP/1.1 200 OK
Date: Sun, 13 Jul 2014 06:20:10 GMT
Server: Apache/2.2.15 (CentOS)
Last-Modified: Sat, 07 Jun 2014 14:29:18 GMT
ETag: "26133e-f3-4fb3fcdaabf43"
Accept-Ranges: bytes
Content-Length: 243
Connection: close
Content-Type: text/html

<html>
<head>
<title>Hello, Tomorrow!</title>
</head>
<body>
<h1>Hello, Tomorrow!</h1>
</body>
</html>

//}

1行目をステータスラインといい
HTTPのバージョンとステータスコードが設定されます。
ステータスコードはレスポンスの結果を表します。
上記の例では"200 OK"になっていますが、これは正常にレスポンスが返せていることを表します。他にリクエストがおかしい事を表す400番台のステータスコードや、サーバ側のエラーを表す500番台のエラーがあります。

2行目以降はヘッダーが続きます。Content-Lengthにはボディの長さが入り、Content-Typeにはボディの種類を返します。text/htmlとはhtmlファイルを表します。この表現方法についてはMIMEタイプで検索してみてください。
他にもたくさんのヘッダーがありますが、現時点で特筆すべきものはありません。気になるヘッダーがあったらそれをキーワードに検索してみましょう。

空行までがヘッダーで、それ以下をボディと言います。ここにレスポンスの実際のデータが入っています。今回はhttp://tomorrowkey.jp/にアクセスしているので、index.htmlがボディに入っています。
ブラウザはこのボディを解釈してWebページとして表示しています。

== ポート番号
１つのホストでは複数のソフトウェアが動いていています。ネットワーク通信をするためにただIPアドレスを指定しただけでは、そのホストのどのソフトウェアとやりとりをしたいのかが分かりません。
リクエストを送るソフトウェアを特定するための番号をポート番号といいます。

各プロトコルによって使われるポート番号は異なります。一部のプロトコルについては一般的に使われるポート番号が決まっています。それらをWell-Known Portといいます。
例えばDNSであれば53で、HTTPであれば80です。すべてを覚える必要がありませんが、よく使われるポート番号くらいは覚えておくと便利です。

== リクエストを送ろう

HTTPリクエストはブラウザでなくてもコマンドとして実行することができます。
LinuxやMacをご使用の方はターミナルやコンソールを使うことができます。
ウインドウが立ち上がったら@<list>{launch-telnet} を実行してサーバと接続しましょう。
//list[launch-telnet][telnetの起動]{
telnet tomorrowkey.jp 80
//}

無事接続できたら@<list>{request-of-http-via-telnet} を実行してください。

Windowsの場合はPuTTYなどのtelnetクライアントをダウンロードする必要があります。 http://www.chiark.greenend.org.uk/~sgtatham/putty/

//image[download-putty][PuTTYのダウンロード画面]{

//}

PuTTYを起動すると設定画面が表示されます。
以下のように接続するサーバの情報などを入力します。

//image[putty-conf-1][PuTTYの設定(1)]{
//}
//image[putty-conf-2][PuTTYの設定(2)]{
//}

Openを押すとコマンドプロンプトのような画面が表示されます。

//image[launch-putty][PuTTYの起動]{
//}

HTTPリクエストを送るための準備が完了したので@<list>{request-of-http-via-telnet} を実行してみましょう。

//list[request-of-http-via-telnet][telnetを使ったHTTP通信のリクエスト]{
telnet tomorrowkey.jp 80
GET / HTTP/1.1
Host: tomorrowkey.jp
User-Agent: telnet

//}


最後に改行を2回することを忘れないようにしてください。
実行してみると次のようなレスポンスが返ってきます（@<list>{response-of-http-via-telnet}）。

//list[response-of-http-via-telnet][telnetを使ったHTTP通信のレスポンス]{
HTTP/1.1 200 OK
Date: Fri, 05 Sep 2014 05:24:41 GMT
Server: Apache/2.2.15 (CentOS)
Last-Modified: Sat, 07 Jun 2014 14:29:18 GMT
ETag: "26133e-f3-4fb3fcdaabf43"
Accept-Ranges: bytes
Content-Length: 243
Content-Type: text/html

<html>
<head>
<title>Hello, Tomorrow!</title>
</head>
<body>
<h1>Hello, Tomorrow!</h1>
<a href="https://mixpanel.com/f/partner"><img src="//cdn.mxpnl.com/site_media/images/partner/badge_light.png" alt="Mobile Analytics" /></a>
</body>
</html>
//}
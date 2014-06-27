= Webサーバ
== 説明すること

本章ではAndroid端末の外側の世界にあたる、Webサーバと通信する際に役に立つ基礎知識を説明します。

== サーバ、クライアント

サーバという言葉は、英語で言えばserverです。
日本語でも、例えば「ジュースサーバ」「ビールサーバ」といった表現で登場します。
@<fn>{server}

//image[juiceserver][ジュースサーバー]{
//}

「ジュースサーバ」は相手にジュースを提供します。
Webサーバは、例えばWebページのような
インターネット・クラウド上にある情報を提供するために存在します。

電子メールの配信に関わる「メールサーバ」もあります。

Word文書を印刷したりするプリンタを利用する人も多いでしょう。
業務用プリンタや最近の家庭用プリンタは、
複数台のパソコンから「このデータを印刷して」という要求を受けて、印刷します。
これも「プリントサーバ」と呼ばれたりします。

//footnote[server][英語名詞であるserverに対応する動詞（「〜する」）はserveです。これは「〜に仕える」「〜のために働く」という意味です。serverのコンピュータ関連の用語ではない本来の意味は「給仕人」「接客係」です。ちなみに給仕の読みは「きゅうじ」であって「きゅうし」ではありません。]

サーバに要求を伝える側を「クライアント」と呼びます。
@<fn>{about_client}
WebブラウザはWebサーバから見てクライアントです。
「Webサーバから見てAndroid端末がクライアントであると」考えてしまっても構いません。
@<fn>{android_maybe_server1}
@<fn>{android_maybe_server2}

//footnote[about_client][日本語でも、お客さんを「クライント」と呼ぶ職業があります。英語でclientです。]
//footnote[android_maybe_server1][本章の範囲ではまず問題ありませんが、Android端末が「常に」クライアントである、と考えるのは間違いです。Andorid端末でもサーバになることはしばしば起こります。実際、Android端末自身をWebサーバにするアプリが存在しますし、簡単なものを実装することは読者の方にも可能です。ただし、全世界にデータを公開する類のWebサーバの役割をするのは難しいです。]
//footnote[android_maybe_server2][クライアントとサーバという表現は、通信を行う場合の「役割」であって、場合によってはこの「役割」が逆転することはありえます。Webサーバからちょっと離れて、複数のAndroid端末間でWiFi経由で対戦ゲームを行うケースを考えましょう。このとき、多くのAndroid端末はクライアントですが、どれか一つはサーバになり、その他の端末からの接続を待つのが一般的です。具体的にはまず、サーバ側がゲームを行うための「部屋」を作り、その他の端末の接続を待ちます。その他の端末はしばしば「ホスト」とも呼ばれるそのサーバへクライアントとして接続します。全員が揃った段階で、ゲームを開始します。このとき、サーバもしくは「ホスト」の役割は別の端末が行うこともありえます。このとき、その別の端末が今度はサーバで、さきほどサーバだった端末はクライアントとなります。]

クライアントであるAndroid端末は、
例えばWebブラウザを経由してWebサーバに情報を取りにいきます。
この場合、ざっくりと言えば

 * Android端末はクライアントとしてサーバにデータを取りに行く
 * サーバはクライアントの要求を受け取り、要求に見合ったデータを返す

という作業が発生します。

== サーバとクライアント間のルール

「クライアントはデータをサーバに取りに行き、
サーバはデータをクライアントに送る」のですが、
では「具体的にどうやって」行うのでしょうか。

「ネットワーク」の章でも学んだ通り、
相手がいる場合には何らかのルールが必要です。
これを「プロトコル」(protocol)と言います。
@<fn>{about_protocol}

//footnote[about_protocol][プロトコルという表現は日常生活ではあまり見ない印象です。ただ、インターネットに関する技術的な話を除くと、国家間の外交に関するニュース等でこの言葉を散見する印象を筆者は持ちます。その場合は「外交儀礼」という意味で、例えば他国の王族をもてなす際には一定の手順、すなわちプロトコルを踏まえるのがならわしです。破ると、ヘタすると外交問題になります。]

特にコンピュータは、基本的にはアドリブに大変弱いです。
サーバとクライアントという二者のやりとりでは
トラブル含めていろいろな状況が起こりえますが、
その状況を可能な限り網羅したプロトコル（つまりルール）
を準備しておき、クライアントとサーバの両方が
その振る舞いにしたがってデータを要求して
データを受け取る必要があります。

「ネットワーク」の章で説明される「TCP/IP」といった
プロトコルだけでは、Webサーバ上のデータを
やりとりするのには不足です。

=== 大山の梅干しを問い合わせる

例えば、近所のスーパー「なるえつ」に
大山の梅干しの在庫があるかを確認するために、
携帯電話から電話をかけたとしましょう。

通話して相手につながりました。
さてそこで、相手が
"Hello, this is Mike. How can I help you?"
と言ってきたとします。
日本語での応答を期待していたとすると、これは困ります。
@<fn>{mike_is_kind}

//footnote[mike_is_kind][日本語で言うと「私はマイクです。何かお手伝いできることはありますか」と言っています。2文目は英語の顧客サポートでしばしば聞く表現で、つまり、多分ですが、この窓口は接客のための窓口で、マイクは、可能性として、なるえつのサポートかもしれません。でも店名言ってません。というわけで筆者なら"Well, am I speaking to Naruetsu Supermarket?"とか聞くような気がしますが、やっぱり勘弁です。]

日本語でスーパーに対して大山の梅干しを問い合わせる場合、
大まかに以下のような流れになるでしょう。

 * 「はい、スーパーなるえつです」
 * 「名前も名乗らぬ客です。大山の梅干しはありますか」
 * 「少々お待ちください……在庫ありました」
 * 「ありがとうございますガチャっ」

ラフに書けばこのくらいの応答がありえます。@<fn>{maniac_explanation}

//footnote[maniac_explanation][厳密ではありませんが、インターネット上でもこのやりとりと似たことが行われています。まず冒頭のサーバ側の返答で、クライアントは少なくとも相手が「スーパーなるえつ」と名乗っていることを理解します。厳密にはスーパーなるえつであるかの証明書が欲しいところですが。次に客は「私は認証されていないユーザです」と延べ、後述するHTPのGETもしくはOPTION要求に相当する形で「大山の梅干し」の在庫確認のクエリを送っています。HTTPで規定がない「少々お待ちください」は曲者ですがおいとくとして、少なくともその要求に対してリソースがあることまではスーパーなるえつサーバは応答します。残念ながらインターネットのようにデータを直接受け取ることはできないので、ここで電話のやりとりは終わりにして、実際に店舗に行った時に売り切れている恐怖と戦います（とりおきプロトコルについては省略）。ちなみにHTTPには「ありがとうございます」を伝えるプロトコルはありません。冗長ですが、ここでお礼も言わずにガチャッてのは現実世界ではあまりやってはいけませんね。]

最初の相手側（サーバーです！）は
電話の応答口が「スーパーなるえつ」
であると言っています。

ここで突然
「今朝、丸ノ内線で、すずらんの花が咲きました」
と語られるのは困ります。

非常に適当な例で恐縮ですが、
「電話がつながる」ことと
「必要な情報を得られる」ことの間には
まだ隔たりがあることがわかります。

クライアントとサーバの話に戻りますと、
「電話がつながる」ところまでが、
言ってみればTCP/IPが保証している領域、
と考えるのが今はわかりやすいと思います。
電話がつながっても、日本語である必要があるし、
日本語にしても適切な応対の幅があるというのもわかります。

== 様々なサーバ
=== Webサーバ

サーバの中でも「Webサーバ」と呼んだ場合、
クライアントはWebサーバに主にWebブラウザ経由で
Webページのようなコンテンツを取得しに行きます。

=== その他のサーバの種類

インターネットやクラウドの世界で登場する
その他のサーバの例としては次のようなものもあります。

 * メールサーバ（電子メールのやりとりに使います）
 * プリントサーバ（プリンタも実はサーバです）
 * ファイルサーバ

=== サーバの種類とプロトコル

種類があるだけクライアントとサーバをつなぐプロトコルが必要です。

 * Webサーバ ... HTTP
 * メールサーバ ... POP, IMAP, SMTPなど
 * プリントサーバ ... IPP, LPR, SMBなど
 * ファイルサーバ ... SMBなど

=== サーバの種類とユーザ視点

ユーザ視点で見ると、必ずしもサーバの分類が
明快に見えないこともあります。

例えばGMailはメールをやりとりするのに使いますが、
読者の多くはWebブラウザでメールを書いて送ります。
さてこの場合、GMailはWebサーバなのか、メールサーバなのか。

この場合、GMailはWebサーバとして、
後述するHTTPに則ってWebページをやりとりします。
ユーザがメールを編集するのも、送信ボタンを押すのも、
HTTP経由で送られるHTML上での操作ですから、
ここはWebサーバの領域です。

一方、送信ボタンクリック後、GMailは要求された
メールに関する送信等の動作を行います。
このとき、実はGMailはメールサーバとして振舞っています。

一般的に「メールサーバ」と呼んだ場合、
そのサーバとクライアント（メールソフト、メーラ）間でのやりとりは
HTTPではなくPOP、IMAP、SMTPといったプロトコルで行います。
実はGMailはこの中でIMAPとSMTPもサポートしています。

GMailのような「Webサーバとしてメール
サービスはYahoo!やMicrosoftといった
会社が提供しており、一般的に「Webメール」と呼びます

Webメールというサービス自体はHTTPを介して
ブラウザとサーバが行うもので、
この場合のサーバはWebサーバです。
メール送信ボタンを押したあと、
Webメールの側は
メールを中継したり配送したりする別のメールサーバ
にメールを送ります。
このときはメールサーバの一種として動作し、
相手のメールサーバと通信する際にも
メールサーバに関わるプロトコルを用います。

クライアント・サーバモデルではしばしば
コンピュータ同士での「対話」が発生しますが、
対話の方法を相手に応じて変更することで、
Webメールサービスはユーザの期待に答えます。

Webページから編集するほかに、
使い慣れたメールソフトでも送受信を行いたい、
という要求があります。
このとき、例えばAndroid付随のメールソフトや
iOSのメールソフトや、Thunderbirdや
OutlookといったソフトからGMailや
その他のWebメールサービスに接続できます。
このときのプロトコルはHTTPではなく
多くの場合POP, IMAP, SMTPとなりますから、
Webメールサービスは純粋にメールサーバとして
動作することになります。

=== Webサーバの重要性は日増しに上がっている

WebメールとWebサーバ・メールサーバの境界について書きましたが、
このあたりのある種の「混乱」は現在のWebサーバを理解する上で大事です。

インターネットの初期は、Webページを閲覧することと、
メールを読むことは別のアプリケーションで行うのが一般的でした。
用途ごとに異なるアプリケーションと異なるプロトコルの組み合わせを
行うのが普通でした。

しかしいろいろな進化と制約により、
Webサーバが何でもできるようにいろいろ作りこんだほうが
便利なのでは、という流れで、技術が発達してきました。

現在では多くのアプリケーションが
HTTPを経由してアプリケーション固有のデータをやりとりします。
以前は（TCPもしくはUDPレベルで）専用のポートを
準備し、その上にのっかるプロトコルを制定していましたが、
現在はHTTPというプロトコルの上で動作させるように
アプリケーション側を変更してしまうことも増えています。
@<fn>{about_rtsp}

//footnote[about_rtsp][IIJが2014年2月に発行したInternet Infrastructure Review Vol.22では動画ストリーミングとしてRTSP（Real Time Streaming Protocol）経由で提供されていたものがHTTP経由でも提供される形になっているといった説明があります。GMail（HTTP+Webサーバ）を使いはじめてからメールソフトを使うことが減ったという人も多いでしょう。]

Android端末からインターネットやクラウドの世界とアクセスする際にはことさらWebサーバとHTTPが重要になります。
サーバとデータをやりとりする際に多くの理由でWebサーバ経由でしかデータが取れないことも多いです。


== Webサーバが従うプロトコル HTTP

一般的な社会でも、ルールはみんなで決めますし、
決まったものは守ります。

Webサーバの場合に使われるのは、
HTTP（Hypertext Transfer Protocol）
というプロトコルです。
このプロトコルの詳細はRFCと呼ばれる文書により定義されます。

=== RFCとは

RFCはRequest For Commentsの略です。
IETF（Internet Engineering Task Force）と呼ばれる
組織によって発行される、技術仕様等に関する文書を指します。
IETFは特にインターネットで利用される標準について議論を行う組織です。
議論する対象に応じてワーキンググループを作成し、
メーリングリストでの議論の後、RFCを発行するなどして
そのワーキンググループの活動を一旦終了します。
TCP/IPに関わる仕様もIETF由来です。

RFCと呼ばれるドキュメントはたくさんあり、それぞれに連番がふられています。
「RFC」のあとに数字をつけ、例えば「RFC 7230」といった形で
特定のRFCを参照します。@<fn>{many_rfc}

//footnote[many_rfc][現時点でも7000を越えるRFC文書があるのは事実ですが、全部がインターネットで活用されている、というわけではありません。特にエイプリルフールに発行されるRFCの中には完全にジョークのものがあります。1998年に公開されたRFC 2324の"Hyper Text Coffee Pot Control Protocol (HTCPCP/1.0)"などはわかりやすい一例です。同RFCの2.3.2 "418 I'm a teapot"は私が学生時代にも衝撃を受けた記憶があります。]

Request For Commentsは日本語に訳すと「コメント求む」なのですが、
実際には各RFCの文書は公開される前に多くの議論を経た上で公開され、公開後に大きな修正は行われません。
そういう意味では、各ドキュメントは「コメント求む」という表現から想像するよりも
はるかに成熟したものです。

仮に改善の必要があった場合には、誤りについてはerrataとして公開されますが、
不足や根本的な改善については次のRFCを議論し、過去のRFCを打ち消す形で次に活かします。

HTTPの仕様を記述するRFCについて見ていきます。



=== HTTPのRFCと改定

HTTPも進化を伴いました。
執筆時点ではHTTPには0.9, 1.0, 1.1があります。
現在2.0の仕様策定中ですが、完成はしていません。

HTTP 0.9が極めてシンプルだったものであったのに対して、
HTTP 1.1の仕様にあたるRFC 2616では、
TXTファイルのページ数にして
実質176ページに渡る長大なものとなっています。

HTTP 1.1は1999年6月に公開されたRFC 2616ですが、
約15年経った今では様々な課題を抱えています。
特に当時は想定されていなかったWebブラウジング以外での
HTTPの利用が増えたことが大きいようです。

== HTTP 1.1 の新RFCについて

RFCは同じ分野で新しい仕様を必要とした場合、
過去のRFCをobsolete（廃止）扱いとすることで
新しい（番号の大きな方の）RFCを利用するよう促します。

2014年6月に、このHTTP 1.1の仕様が
15年ぶりに改定されました。現在ではその内容が
下記6つのRFCとして公開されています。

* RFC7230: Message Syntax and Routing
* RFC7231: Semantics and Content
* RFC7232: Conditional Requests
* RFC7233: Range Requests
* RFC7234: Caching
* RFC7235: Authentication

(TODO: 概要説明)

この改定では、HTTPのバージョンが増えたわけではありません。
HTTP 1.1と呼ぶとき、今後はRFC 2616ではなく上記のRFCのみを参照するようにしてください。
ちなみに、
RFC 7230に関わっているMark Nottingham氏は自身のブログ記事"RFC2616 is Dead"（RFC2616 は死んだ）
@<fn>{mark_nottingham}で、
「RFC2616は使わないでください。ハードドライブ、ブックマークから削除し、
印刷されているなら全て燃やしてしまうかリサイクルに回しましょう」とまで書いています。 
HTTP 1.1について深く調べる際には、RFCを参照することはもちろんですが、関連記事を読む際に、古いRFCを元にしていないかを気にするのは良いことでしょう。@<fn>{old_rfc_wont_fade}

//footnote[mark_nottingham][@<href>{https://www.mnot.net/blog/2014/06/07/rfc2616_is_dead}]

//footnote[old_rfc_wont_fade][古いRFCを直接見ると、実はこのobsoleteとなったことに関する情報は記載されていません。これは利用者からみて少し面倒な事態を引き起こします。特にHTTP 1.1の古い側の仕様であるRFC 2616は現在でも公開されており、そこには、新しいRFC 7230〜7235を代わりに参照すべし、とは書いていません。一般的に公開されたRFC自体は一切修正されません。errataや別のRFCで上書きをするだけです。そのため、RFCを参照する側が情報収集を怠っていると、知らずのうちに古いRFCを参照する問題が発生します。さて執筆現在、Googleで「HTTP RFC」と検索します。すると、古い方のRFCが検索結果のトップとなります。長いこと参照されているのですから、ある意味当然です。しかし何も知らずにいると、それが実は参照してはいけないRFCだということに、気づくことがありません。他のWebサイトにおいてObsoleteとなったRFCは簡単に調べられますし、ニュースで取り上げられるケースもあります。単体のRFCを仕様書として絶対のものとは見ないようにしてください。]

=== HTTP 2.0 について

HTTP 2.0はHTTP 1.1の次バージョンとして標準化が行われている次のHTTP仕様です。
Googleが開発しているSPDFと呼ばれる仕組みを元にしています。

仕様策定としては最終段階にありますが、
「そもそもこれを公式の仕様とするべきではない」
と主張する人々もいます。


http://www.phoronix.com/scan.php?page=news_item&px=MTcwMTA

===[column] RFCへの「コメント」は誰でもできる

RFCが「仕様」ということで、
とても偉大で近づきがたい印象を持ってしまうこともあります。
筆者もその一人です。

ところで筆者は、あるRFCのワーキングループに積極的に参加したことがあります。
当時ある事情で特定のプロトコルを実装する必要があったのですが、
プロトコルに抜けがあって困っていました。
おそらく初期のバージョンでは検討から抜けていたのでしょう。

ちょうどその時、知り合いからそのプロトコルの次世代バージョンの
RFCが議論されていると聞き、個人のメールアドレスを使って
MLでの議論に参加することにしました。

変更としては非常にシンプルで説得力があったせいか、
特に何の異議もなく採用され、
RFCのAcknowledgementの項に名前が掲載されました。
こういうことは、普段ないだけに結構うれしいものです。

ここで大事なことは、
IETFでの議論は一般に広く開かれているということです。
迷惑と判断されるような行動をおこさなければ、
一介の技術者が世界的に使われる仕様に意見を出すことはいつでも可能です。

ただし、議論は英語です。


=== Android アプリからWebサーバからデータを取得する

実際にAndroid経由でHTTPアクセスをしてみましょう。
ここでは@<code>{java.net.HttpURLConnection}を用いることにします。

===[column] DefaultHttpClientとAndroidHttpClient について

HTTPアクセスを行うライブラリは他にも@<code>{org.apache.http.impl.client.DefaultHttpClient}や
@<code>{android.net.http.AndroidHttpClient}といったライブラリが紹介されることがあります。
しかし本稿ではそれらの理由はおすすめしません。
現時点でこれらの実装にはバグが多く、今後もメンテナンスされる見込みがないと考えられているためです。
なお、非常に古いAndroidのバージョン（2.2）では@<code>{java.net.HttpURLConnection}にバグがあったため、
それらの古いバージョンでは注意が必要です。

 * 参考: Android Apache HTTP Client と HttpURLConnection どっちを使うべき？ @<href>{http://y-anz-m.blogspot.jp/2011/10/androidapache-http-client.html}@<fn>{this_is_also_old_article}


//footnote[this_is_also_old_article][記事の公開2011年10月4日に公開された点も出来れば]



== UrlHttps を試す
== SSL

== 認証・認可について

 * 認証: 本人確認
 * 認可: アクセス許可

コンピュータの世界から離れて役所で公的な証明書を受け取ることを考えてみます。
例えば、戸籍。

申請書類を書いて、免許証と申請書類を提出し、
役所が大丈夫だと思えば、役所が持っている情報を提供してくれます。

免許証を見せることは自分が本人であることの確認です。
もし「自分である」ことがわかれば、方法は複数あります。


しかし、見せたからと言って、申請する書類の許可が常に得られるとは限りません。

== ぼこぼこぼこぼ

 * JavaScript
 * Authentication / Authorization
 * REST / RESTful
 * XML, JSONの概要
 * HttpURLConnection を試す
 * クッキーによる状態の保存

 * データを保存・共有するために必要
 * BaaS
 * Webブラウザから見える「独立のアプリケーション」
 * SaaS
 * AWS
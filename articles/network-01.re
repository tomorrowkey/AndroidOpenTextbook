= ネットワーク

Webサーバーと連携して最新のデータを取得したり、他のプラットフォームと同期するためにデータを送信したりする際にネットワークの知識が必要になります。
この章ではHTTPサーバからファイルを取得する様々な方法を通してネットワーク通信の仕組みを学びます。

== Androidアプリでネットワークを使うために必要なパーミッション

インターネットに接続するにはandroid.permission.INTERNET というパーミッションが必要なので、AndroidManifestに宣言します。

//list[internet-permission][インターネットパーミッション]{
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
          package="com.example.sample.network">

  <uses-permission android:name="android.permission.INTERNET" />

  <application
   ...
//}

=== Androidで使用できる通信方式

Androidが搭載される端末は以下のような通信方式を持っています。

 * Mobile
 ** 3G
 ** LTE
 ** WiMAX
 * Wi-Fi
 * Bluetooth
 * NFC

3GにもCDMAやHSDPAなど種類がありますがアプリ開発者が意識することはあまりなく、意識することがあってもWi-Fiに接続中なのか、もしくはMobileなのかくらいです。
厳密にはもうすこし通信方式はありますが、あまり一般的ではないので省略します。
この章ではHTTP通信を行う通信方法を紹介します。上記リストの中ではMobileとWi-Fiが該当します。

=== モバイルという性質
ネットワークと語る上で、サーバーのアプリケーションやデスクトップ向けアプリケーションとくらべて、２つの大きな特徴があります。
一つはネットワークは不安定ということと、もう一つは電池消費量に気をつけなくてはならないということです。

==== ネットワークは不安定

Androidを搭載した端末の多くは携帯電話です。様々な場所に持ち歩く携帯電話なので、必ずしもネットワークに恵まれた場所にいるとは限りません。
アプリを作るにあたっていつネットワークが切れても問題ないように作らなくてはなりません。
また、ネットワークが切れてしまった場合にユーザーにストレスをかけないような作りを心がけることも重要です。

==== 電池消費量

電池消費量にも気を配らなくてはなりません。モバイルで電池を消耗しやすい機能の１つがネットワーク通信です。
できるだけ通信料を減らす、通信回数を減らす、一度まとめてに通信するといった事を心がけると、電池消費にも優しいアプリを作ることができます。

=== メインスレッドと非同期スレッド
理論値では100Mbpsを越えるネットワークでも環境によっては数百bpsしかでないため、小さいデータのやりとりであっても時間がかかるものだと考えるべきです。
時間のかかる処理はUIスレッドで行ってはいけません。必ず非同期処理ができる仕組み（AsyncTaskなど）を使うようにしましょう。

== ソケットプログラミング
Androidで一番低レベルなネットワーク通信方法はSocketを使ったやり方です。
OSI参照モデルではトランスポート層以下が提供されます。
HTTPサーバーにアクセスするにはすこし貧弱ですが、HTTP以外のサーバにアクセスすることができるため便利です。
例えばhttp://tomorrowkey.github.io にアクセスしようとした場合、以下のようなプログラムになります。

//list[basic_implemention_of_socket][Socketの実装方法]{
try {
  // リクエスト
  Socket socket = new Socket();
  socket.connect(new InetSocketAddress("tomorrowkey.github.io", 80));

  String request = "GET / HTTP/1.1\n" +
    "Host: tomorrowkey.github.io\n" +
    "\n\n";
  OutputStream outputStream = socket.getOutputStream();
  outputStream.write(request.getBytes());
  outputStream.flush();

  // レスポンス
  InputStream inputStream = socket.getInputStream();
  byte[] buffer = new byte[1024];
  int length;
  while ((length = inputStream.read(buffer)) != -1) {
    Log.d("TEST", new String(buffer, 0, length));
  }

  outputStream.close();
  inputStream.close();
} catch (UnknownHostException e) {
  throw new RuntimeException(e);
} catch (IOException e) {
  throw new RuntimeException(e);
}
//}

=== リクエスト
まずはSocketインスタンスを生成します。
//list[make-instance-of-socket][Socketインスタンスの生成]{
Socket socket = new Socket();
//}

Socketインスタンスができたら、ホスト名とポート番号の接続先を指定します。
今回はHTTPなので、ポート番号は80番になります。
//list[set-host-and-port-number][ホスト名とポート番号の指定]{
socket.connect(new InetSocketAddress("tomorrowkey.github.io", 80));
//}

Socketでリクエストする場合、OutputStreamに直接HTTPリクエストを書きます。
//list[request-with-socket][リクエストの送信]{
OutputStream outputStream = socket.getOutputStream();
outputStream.write(request.getBytes());
outputStream.flush();
//}

=== リクエストの組み立て

Socketで通信を行う場合、プロトコルに従った通信内容を自分で組み立てる必要があります。
今回はHTTP通信なので、HTTPのプロトコルに従ったリクエストを自分で組み立てます。

Webサーバからページを取得する命令はGETです。
一番単純なGETリクエストは以下のようになります。

//list[get-request][GETリクエスト]{
GET / HTTP/1.1
Host: tomorrowkey.github.io

//}

1行目には大まかなリクエスト内容を送ります
//table[the-first-line-of-get-request][GETリクエスト1行目]{
-----------------------
GET				ファイルを取得する
/					"/"というファイルを取得する。"/"とリクエストすると、大抵のWebサーバでは"/index.html" と解釈されます。
HTTP/1.1	HTTP/1.1というプロトコル（手続き方法）を使います
//}

2行目からはリクエストヘッダ（リクエスト時の付属情報）を送信します
//table[the-second-line-of-get-request][GETリクエスト2行目]{
-----------------------
Host:									ヘッダのキーです
tomorrowkey.github.io	Hostキーはリクエスト先のホスト名を指定します
//}

リクエストの最後に改行を2回送るとリクエスト完了となります。

=== レスポンス

socketからInputStreamを取得してHTTPレスポンスを取得します。

//list[get-response-body-with-socket][レスポンスの取得]{
InputStream inputStream = socket.getInputStream();
byte[] buffer = new byte[1024];
int length;
while ((length = inputStream.read(buffer)) != -1) {
  Log.d("TEST", new String(buffer, 0, length));
}
//}

レスポンスの取得まで完了したらInputStreamとOutputStreamのcloseメソッドを呼んでStreamを閉じましょう。

=== 実行結果
実行するとlogcatにレスポンスが出力されます。
//list[response-of-socket-request][Socketを使ったリクエストのレスポンス]{
D/TEST    ( 1371): HTTP/1.1 200 OK
D/TEST    ( 1371): Server: GitHub.com
D/TEST    ( 1371): Content-Type: text/html; charset=utf-8
D/TEST    ( 1371): Last-Modified: Mon, 02 Jan 2012 05:54:49 GMT
D/TEST    ( 1371): Expires: Mon, 30 Jun 2014 11:37:13 GMT
D/TEST    ( 1371): Cache-Control: max-age=600
D/TEST    ( 1371): Content-Length: 169
D/TEST    ( 1371): Accept-Ranges: bytes
D/TEST    ( 1371): Date: Mon, 30 Jun 2014 12:24:02 GMT
D/TEST    ( 1371): Via: 1.1 varnish
D/TEST    ( 1371): Age: 3409
D/TEST    ( 1371): Connection: keep-alive
D/TEST    ( 1371): X-Served-By: cache-ty66-TYO
D/TEST    ( 1371): X-Cache: MISS
D/TEST    ( 1371): X-Cache-Hits: 0
D/TEST    ( 1371): X-Timer: S1404131042.773465872,VS0,VE174
D/TEST    ( 1371): Vary: Accept-Encoding
D/TEST    ( 1371): 
D/TEST    ( 1371): <html>
D/TEST    ( 1371): <!DOCTYPE html>
D/TEST    ( 1371): <html lang="ja">
D/TEST    ( 1371): <head>
D/TEST    ( 1371): <title>tomorrowkey GitHub page</title>
D/TEST    ( 1371): <meta charset="UTF-8" />
D/TEST    ( 1371): </head>
D/TEST    ( 1371): <body>
D/TEST    ( 1371): <h1>Hello, tomorrow!!</h1>
D/TEST    ( 1371): </body>
D/TEST    ( 1371): </html>
//}

HTTPレスポンスのheaderとbody両方が出力されました。
Socketで通信する場合はこの文字列をJavaのオブジェクトに変換する処理が必要です。
リクエストを自分で組み立てないといけなかったり、レスポンスが生データのままなので大変ですが、とても自由度が高いのが特徴です。

== HttpURLConnection

Socketではリクエストを自分で組み立てなければなりませんでしたが、HTTP/HTTPSにアクセスする場合もっと便利なクラスがあります。それがHttpURLConnectionです。
それでは先ほどと同様http://tomorrowkey.github.ioにアクセスしてみましょう。

//list[basic-implemention-of-http-url-connection][HttpURLConnectionの実装方法]{
try {
  URL url = new URL("http://tomorrowkey.github.io");
  HttpURLConnection connection = (HttpURLConnection) url.openConnection();
  connection.setRequestMethod("GET");
  connection.setRequestProperty("Host", "tomorrowkey.github.io");
  connection.connect();

  int responseCode = connection.getResponseCode();
  Log.d("TEST", "responseCode=" + responseCode);
  String contentLength = connection.getHeaderField("Content-Length");
  Log.d("TEST", "Content-Length=" + contentLength);
  String contentType = connection.getHeaderField("Content-Type");
  Log.d("TEST", "contentType=" + contentType);

  InputStream inputStream = connection.getInputStream();
  String body = readToEnd(inputStream);
  Log.d("TEST", "body=" + body);
  inputStream.close();
} catch (MalformedURLException e) {
  throw new RuntimeException(e);
} catch (IOException e) {
  throw new RuntimeException(e);
}
//}

=== リクエスト

アクセスするURLを使いURLオブジェクトを作ります。
//list[make-a-instance-of-url][URLオブジェクトの生成]{
URL url = new URL("http://tomorrowkey.github.io");
//}

openConnection()メソッドを使い、HttpURLConnectionを取得します。
//list[get-http-url-connection][HTTPUrlConnectionの取得]{
HttpURLConnection connection = (HttpURLConnection) url.openConnection();
//}
注意しなければならないのが、URL.openConnection()の戻り値はURLConnectionなのでHttpURLConnectionにパースしなければならないということです。

リクエストはファイルの取得なので、setRequestMethod()メソッドで"GET"を渡します。
また、setRequestProperty()メソッドを使うことでリクエストヘッダーを設定することができます。
Hostは設定しなくても自動的に追加させるのですが、あえて追加しました。
//list[set-request-method][リクエストの設定]{
connection.setRequestMethod("GET");
connection.setRequestProperty("Host", "tomorrowkey.github.io");
//}

connectメソッドでサーバと接続します。
//list[connect-to-the-server][サーバとの接続]{
connection.connect();
//}

=== レスポンス

ステータスコードを取得する場合、getResponseCode()メソッドを呼びます
//list[get-status-code-from-http-url-connection][ステータスコードの取得]{
int responseCode = connection.getResponseCode();
Log.d("TEST", "responseCode=" + responseCode);
//}

レスポンスヘッダを取得する場合、getHeaderField()メソッドを呼びます

//list[get-headers-from-http-url-connection][レスポンスヘッダの取得]{
String contentLength = connection.getHeaderField("Content-Length");
Log.d("TEST", "Content-Length=" + contentLength);
String contentType = connection.getHeaderField("Content-Type");
Log.d("TEST", "contentType=" + contentType);
//}

レスポンスボディを取得する場合、getInputStream()メソッドを呼びます
//list[get-body-from-http-url-connection][レスポンスボディの取得]{
InputStream inputStream = connection.getInputStream();
String body = readToEnd(inputStream);
Log.d("TEST", "body=" + body);
//}
InputStreamから文字列に変換する処理はSocketと同じなので、メソッド化しました。

=== 実行結果

//list[response-of-http-url-connection-request][HttpURLConnectionを使ったリクエストのレスポンス]{
D/TEST    ( 1231): responseCode=200
D/TEST    ( 1231): Content-Length=null
D/TEST    ( 1231): contentType=text/html; charset=utf-8
D/TEST    ( 1231): body=<html>
D/TEST    ( 1231): <!DOCTYPE html>
D/TEST    ( 1231): <html lang="ja">
D/TEST    ( 1231): <head>
D/TEST    ( 1231): <title>tomorrowkey GitHub page</title>
D/TEST    ( 1231): <meta charset="UTF-8" />
D/TEST    ( 1231): </head>
D/TEST    ( 1231): <body>
D/TEST    ( 1231): <h1>Hello, tomorrow!!</h1>
D/TEST    ( 1231): </body>
D/TEST    ( 1231): </html>
//}

Socketとは異なりHTTPプロトコルを楽に使えるようなメソッドが用意されているため、簡単に取り扱うことができます。

== HttpClient (Apache Http)
GET / POST
InputStream / OutputStream

AndroidではApacheのHttpClientが標準で入っているので、HttpClientも使うことができます。
こちらも先ほどと同様のアクセスをしてみましょう。

//list[basic-implementation-of-http-client][HttpClientの実装方法]{
try {
  HttpGet httpGet = new HttpGet("http://tomorrowkey.github.io");
  httpGet.addHeader("Host", "tomorrowkey.github.io");

  HttpClient httpClient = new DefaultHttpClient();
  HttpResponse httpResponse = httpClient.execute(httpGet);

  InputStream inputStream = httpResponse.getEntity().getContent();
  int length;
  byte[] buffer = new byte[1024];
  while ((length = inputStream.read(buffer)) != -1) {
    Log.d("TEST", new String(buffer, 0, length));
  }
  inputStream.close();
} catch (MalformedURLException e) {
  throw new RuntimeException(e);
} catch (IOException e) {
  throw new RuntimeException(e);
}
//}

=== リクエスト
GETリクエストなので、HttpGetオブジェクトを作ります。引数にはアクセスするURLを指定します。
//list[make-a-instance-of-http-get][HttpGetオブジェクトの生成]{
HttpGet httpGet = new HttpGet("http://tomorrowkey.github.io");
//}

ヘッダの指定はaddHeaderメソッドを使います。
//list[add-header-to-http-get][ヘッダーの追加]{
httpGet.addHeader("Host", "tomorrowkey.github.io");
//}

実際に通信を行うのはHttpClientというオブジェクトなので、HttpClientを生成します。
今回はDefaultHttpClientを使ってHttpClientを生成していますが、AndroidHttpClientを使うこともできます。

//list[make-a-instance-of-http-client][HttpClientの生成]{
HttpClient httpClient = new DefaultHttpClient();
//}

生成したhttpClientのexecute()メソッドにリクエストオブジェクト(httpGet)を渡すことで通信をします。
//list[communicate-with-http-client][HttpClientを使った通信]{
HttpResponse httpResponse = httpClient.execute(httpGet);
//}
通信したレスポンスはHttpResponseというクラスで戻り値に返ってきます。

=== レスポンス


ステータスコードを取得するには、まずはgetStatusLine()メソッドでステータスラインを取得した後に、getStatusCode()メソッドを呼びます。
//list[get-status-code][ステータスコードの取得]{
StatusLine statusLine = httpResponse.getStatusLine();
Log.d("TEST", "Status-Code=" + statusLine.getStatusCode());
//}
ステータスラインとはHTTPレスポンスの以下の部分を指します。
//list[status-line][ステータスライン]{
HTTP/1.1 200 OK
//}

レスポンスヘッダを取得するには、getFirstHeader()メソッドでHeaderオブジェクトを取得します。
Headerオブジェクトの値を取得するにはgetValue()メソッドを呼びます。
//list[get-header][ヘッダーの取得]{
Header contentLengthHeader = httpResponse.getFirstHeader("Content-Length");
Log.d("TEST", "Content-Length=" + contentLengthHeader.getValue());
Header contentTypeHeader = httpResponse.getFirstHeader("Content-Type");
Log.d("TEST", "Content-Type=" + contentTypeHeader.getValue());
//}

レスポンスボディを取得する場合、getInputStream()メソッドを呼びます

//list[get-response-body][レスポンスボディの取得]{
InputStream inputStream = httpResponse.getEntity().getContent();
String body = readToEnd(inputStream);
Log.d("TEST", body);
inputStream.close();
//}

リクエストとレスポンスのオブジェクトが分かれているので分かりやすいですね。

=== 実行結果

//list[response-of-http-client-request][HttpClientを使ったリクエストのレスポンス]{
D/TEST    ( 1295): Status-Code=200
D/TEST    ( 1295): Content-Length=169
D/TEST    ( 1295): Content-Type=text/html; charset=utf-8
D/TEST    ( 1295): <html>
D/TEST    ( 1295): <!DOCTYPE html>
D/TEST    ( 1295): <html lang="ja">
D/TEST    ( 1295): <head>
D/TEST    ( 1295): <title>tomorrowkey GitHub page</title>
D/TEST    ( 1295): <meta charset="UTF-8" />
D/TEST    ( 1295): </head>
D/TEST    ( 1295): <body>
D/TEST    ( 1295): <h1>Hello, tomorrow!!</h1>
D/TEST    ( 1295): </body>
D/TEST    ( 1295): </html>
//}

== メッセージキューとか

== ライブラリを使ったネットワーク通信

 * Volley https://android.googlesource.com/platform/frameworks/volley/
 * okhttp https://github.com/square/okhttp
 * Picasso https://github.com/square/picasso





EOF
= ユーザーインターフェースとは？

実際にアプリを作っていく上で必要な画面のレイアウトやデザイン。これらを、「ユーザーが操作していくもの」という意味も含めて、@<b>{ユーザーインターフェース（UI）}と呼びます。
たとえば、テキストを入力するエディタや、押すと何かが起こるボタンなどです。また、操作するわけではないですが、アプリの重要な要素として、テキストや画像などもユーザーインターフェースのひとつです。

インターフェースは、機械と人間とをつなぐ重要な接点ともいえます。
何をすれば何が起こるのか、ということを瞬時にユーザーに知らせなければなりません。
たとえば、ボタンは押すことができますが、そもそも「押せる」ということをユーザーに知らせなければなりません。
これについては、ユーザーにアフォーダンス@<fn>{affordance}を与えることが重要だといわれています。

//footnote[affordance][1988年、ドナルド・ノーマンはデザインの認知心理学的研究の中で、モノに備わった、ヒトが知覚できる「行為の可能性」という意味でアフォーダンスを用いた。この文脈によるアフォーダンスという語義が、ユーザーインタフェースやデザインの領域において使われるようになった。アフォーダンスは、物をどう取り扱ったらよいかについての強い手がかりを示してくれる。たとえば、ドアノブがなく平らな金属片が付いたドアは、その金属片を押せばよいことを示している。逆に、引き手のついたタンスは、引けばよいことを示している。これらは、体験に基づいて説明なしで取り扱うことができる(Wikipediaより)]


//image[affordance][アフォーダンスを利用したユーザーインターフェースの例][scale=0.5]{
//}

@<img>{affordance}を見ると、その意味が少しわかるでしょうか。
ボタンは、「押せる」ことを強調するために少し立体的に見せる工夫をしてあることが多いです。
また、クリック時（押されたとき）には凹んだように見せることでによって、ユーザーに「ボタンを押した」ことを認識させています。

普段使っているパソコンにも、たくさんのアプリケーションがあります。
文書やドキュメントの作成であればMicrosoft Office、画像の作成であればAdobeなどのグラフィックツール、他にもたくさんあるでしょう。
パソコンで使うアプリケーションのインターフェースもいろいろとアフォーダンスを与える工夫がなされていますが、これらは@<b>{キーボードとマウスで使うことに最適化されて考えられています}。

少し前まではそれだけでよかったのですが、2007年にiPhoneが発売されてから、わたしたちの業界もガラッと様子が変わりました。
Androidをはじめとした@<b>{スマートフォンは指で触れることによって操作する}のです。

今までデザイナーは、キーボードとマウスを使うようなインターフェースを作ることには慣れており、ノウハウの蓄積もありました。
しかし、タッチデバイスによるインターフェースの作成は、誰もがはじめてだったのです。しかも、パソコンとは違って画面サイズもかなり小さいので、使える領域も限られています。
このような制約の中でインターフェイスをつくることは、多くの試行錯誤を必要としました。

iPhoneの登場から7年が経った今、タッチデバイスでのインターフェースのノウハウもたまりつつあります。

昨今において、インターフェースの設計は、デザイナーもプログラマもみんなが知っておかなければならない重要なものとなりつつあります。
実際にアプリケーションを作るときにも避けては通れない道です。ただ、その重要性のわりには体系的に教えることがむずかしい分野でもあります。なぜなら暗黙的なノウハウ、経験値に支えられている分野だからです。興味のある方は、ぜひ書店などでデザインの専門書を読むことをおすすめします。きっと、世の中に対する物事の見方が変わります（笑）。

とはいえ、そこまでしなくても、普段みなさんが使っているアプリケーションで（パソコンでもスマートフォンでもかまいません）、どこにアフォーダンスが使われているかを考えてみましょう。よいインターフェースの勉強になりますのでぜひ実践してみてください。

== Androidアプリのユーザーインターフェース

さて、一般的なインターフェースについては上述のとおりですが、Androidアプリを作るときには、それに沿ったインターフェースを知っておかなければなりません。
なぜなら、Android OSを提供しているGoogleが、「Androidアプリはこう作りなさい」というガイドラインを作成しているからです。

//image[guideline][Googleが定めているAndroidアプリのガイドライン（@<href>{http://developer.android.com}/）]{
//}

このガイドラインの中には、「Design」「Develop」「Distribute」という3つのカテゴリがあり、すべてのインターフェースを知るためには、それを実際にコードでかいて実現できなければなりません。
しかし、今の段階ではそこまでせずとも、まずは「どんなインターフェースがあるのか」をだいたいでいいので知っておきましょう。これを知らなければ、アプリの設計ができないからです。
しっかりとしたAndroidアプリを作りたいならば、早いうちからこのガイドラインを読んでおくべきです。

英語だし読めない…といわず、Googleの翻訳機能などを使ってでもいいので、頭に入れておくようにしましょう。
もし、内容がよくわからなくても、ここにある図だけでも見ておくよいでしょう。これらはすべてガイドラインに沿ったAndroidアプリのデザインになっていますので、実際に設計するときに役に立ちます。

学習が進んでくると、そのうち全部を読まなければならないのですが、はじめは、

 * Design > Style（@<img>{guideline-design-style}）
 * Design > Patterns（@<img>{guideline-design-patterns}）
 * Design > Building Blocks（@<img>{guideline-design-blocks}）

の3つに目を通しておくとよいでしょう。


//image[guideline-design-style][Design > Style画面][scale=0.2]{
//}


//image[guideline-design-patterns][Design > Patterns画面][scale=0.2]{
//}


//image[guideline-design-blocks][Design > Building Blocks画面][scale=0.2]{
//}

== iPhoneアプリとAndroidアプリのインターフェースの比較

Androidアプリにはガイドラインがあるといいましたが、もちろんiPhoneアプリにもガイドラインはあります。
iPhoneアプリのほうが厳しく、アプリを公開するときには、ガイドラインを準拠しているか、という審査があるからです。iPhoneアプリの場合は、少しでもガイドラインから逸脱したものがあれば、リジェクト@<fn>{reject}され、公開することができません。

//footnote[reject][アプリが公開されずに差し戻されること。リジェクトされると、審査時にNGだったところを修正して、再度申請しなければならない]

それではAndroidのほうは審査がないのかと安心してはいけません。Androidアプリは、事後審査になります。公開時の審査は基本的にはありませんが、公開後に、Webの検索エンジンと同様にGoogle Playでキーワードなどをクロールし、NGワードなどがあれば警告されるようになっているようです@<fn>{android-judge}。警告を無視し続けると、Googleアカウント自体が停止され、Googleに関するすべてのサービスが一時利用できなくなってしまうので注意してください@<fn>{akaban}。

//footnote[android-judge][@<href>{http://technica.speee.jp/803} を参照]
//footnote[akaban][アカBAN、Account banといい、開発者が最も恐れていることです]

iPhoneアプリとAndroidアプリでは、推奨されるインターフェースにも違いがあります。
これは、それぞれのOSを構成している言語、フレームワークの思想の違いにもよります。

iPhoneアプリはObjective-CまたはSwift（iOS 8以降）という言語や、ストーリーボードなど専用のレイアウトツールを基準にインターフェースが定められています。
Androidアプリを構成する言語はJavaであり、レイアウトはXMLで作ることになります。こちらも、Android OSに合うようなインターフェースが定められています。

なぜこのようなことを言うかというと、iPhoneアプリのインターフェースをそのままマネしたようなAndroidアプリをよく見かけるからです。
iPhoneアプリのインターフェースをAndroidアプリでマネする必要はまったくありません。
先述のとおり、それぞれのOSでの構成や思想が違い、さらにその言語を使って最適化できるインターフェースも違います。
無理やりどちらかのOSのインターフェースにあわせることは、アプリを作っていく上で、無駄な設計が多くなってしまうことに注意してください。

いちばんわかりやすいのは、設定アプリを比較することです（@<img>{comp-setting}）。

//image[comp-setting][設定画面（左：Android、右：iOS）]{
//}

@<img>{comp-setting}のAndroidとiOSでは、いろいろな相違点があります。
どういったことが違うか、グループで話し合い、箇条書きで書き出してみましょう。

 * 
 * 
 * 
 * 
 *

Androidアプリに設定画面を設けるとしたら、このようなデフォルトの設定アプリに近いデザインの採用が推奨されています。また、同じようなデザインであれば、事前に用意されたデフォルトのコードを使い、少しだけカスタマイズをするだけで実装できるでしょう。

=== その他のアプリの比較

他にも、iPhone/Androidの両OSに同じサービスを提供しているアプリのインターフェースを比較すると、それぞれのOSのインターフェースを学ぶ上で大変参考になります。
Facebook、Twitter、Foursquare、Dropboxを挙げておきます。これらに対しても、それぞれの相違点を箇条書きで書き出してみましょう。




Facebookアプリのインターフェースの相違点を書き出してみましょう（@<img>{comp-facebook}）。

//image[comp-facebook][Facebook（左：Android、右：iOS）]{
//}

インターフェースの相違点

 * 
 * 
 * 
 * 
 *


Twitterアプリのインターフェースの相違点を書き出してみましょう（@<img>{comp-twitter}）。

//image[comp-twitter][Twitter（左：Android、中央：Androidのメニュー、右：iOS）][scale=0.2]{
//}

インターフェースの相違点


 * 
 * 
 * 
 * 
 *


Foursquareアプリのインターフェースの相違点を書き出してみましょう（@<img>{comp-foursquare}）。

//image[comp-foursquare][Foursquare（上段：Android、下段：iOS）]{
//}

インターフェースの相違点

 * 
 * 
 * 
 * 
 *

Dropboxアプリのインターフェースの相違点を書き出してみましょう（@<img>{comp-dropbox}）。

//image[comp-dropbox][Dropbox（左：Android、中央：Androidのメニュー、右：iOS）]{
//}

インターフェースの相違点

 * 
 * 
 * 
 * 
 *

このように見てみると、AndroidにはAndroidのインターフェースの特徴が、iPhoneにはiPhoneのインターフェースの特徴がみえてきます。
これらをしっかりと認識し、AndroidとiPhoneを混同しないようにしましょう。

こういった比較は、日常で、普段使っているアプリでもできるので、アプリを使うときにはただ使うだけではなく、どういうインターフェースが使われているか、注意してみましょう。そうすると、アプリに対する見方が180度変わってきます。

また、Androidアプリを作るならば、本来なら普段からAndroidを使って、Androidの習慣に慣れておくことが望ましいです。
ときどき、Androidアプリのデザインをするデザイナーが、Androidを使ったことすらなく、インターフェースについてもまったく知らなくてビックリすることがあります（プロのデザイナーが、です）。

アプリ開発は、プログラムの技術があればよい、というものではありません。
今や、デザインのほうが重要だとも言われる時代です。使う人に「使いやすい」「使ってたのしい」と思ってもらえないと、すぐに飽きられてしまいます。

アプリを作ることも大切ですが、その前にまずこの章に書かれていることをしっかりと理解し、ガイドラインを読み、AndroidというOSのインターフェースや習慣を知っておくべきです。
今からそれに気をつけていれば、きっと素晴らしいアプリが作れるようになるでしょう。

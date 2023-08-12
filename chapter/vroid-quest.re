=[nonum] 手っ取り早くVRoidアバターをQuest対応させる方法

== はじめに

イメージに合うVRChatのアバターがいないときの強い味方がVRoid Studioです。
このVRoid Studioは無料で使え、けっこう望んだ姿のアバターを作ることができます。
しかも、BOOTHなどで頒布されている衣装テクスチャを使えば、アバターのバリエーションはさらに広がるでしょう。
そのため、私がVRChatにいるとき、だいたいVRoid Studioで作成したアバターを使っています。
私はVRChatにはPC版から入りましたが、初めて入ったのがQuestユーザーのイベントだったので早い段階でアバターのQuest対応を意識しています。
しかし、VRChatのQuest版ではシェーダーが限定され、透過が使えないなどの厳しい制限があります。
他のアバターならポリゴン数を削れば何とかなるのですが、VRoid製アバターの場合テクスチャに透過をかなり多く使っているため対応にコツがいります。
しかしながら、大体これならちょうどよいという改変方法を見つけたので共有します。
なお、この本は過去にUnityを使ってアバターをアップロードしたことがある人向けとなっております。
既出だったり、手ぬるいと言われたりするかもしれませんが、ご笑納いただければ幸いです。

== Questアバターへの制限

VRChatのQuest版やAndroid版でアバターを使うには以下のような制限があります。
まずはじめに、VRChat公式ではQuestで使用するアバターはポリゴン数を10,000以下にすることを推奨@<bib>{VRCQuest}しています。
そして、VRChatのアバターは表示のしやすさに応じてランクが付けられています。
非常に軽くて表示しやすいExcellentのアバターを作るのはよほど単純化しないといけません。
ランクがExcellentやGoodならQuestで表示できないアバターを使っているときに表示するFallbackアバターにすることができますが、多くのアバターはPoorかVeryPoorになってしまうと思います。
イベントによっては重くなるのでVeryPoorのアバターを使っている人の参加をお断りすることがあり、PoorランクやMediumランクを目指す改変者も多いです。

で、公式の情報@<bib>{VRCPerformanceRanks}によれば、Quest版アバターのランク付けについては以下の通りとなっています。

//image[quest-avatar-ranks][Quest版アバターのランク付け]{
    VRChat公式より
//}

なお、Quest版で初期状態で見えるランクはMediumであり、使っているアバターがMediumランクに対応していればQuestの人から初期状態で見えることになります。
しかし、Mediumランクでさえこれを実現するのは難しいです。
ましてや、Fallbackアバターを目指すのは至難の業と言うことがお分かりでしょう。

== 改変方針

私はQuest対応アバターを作る時、以下のような改変方針にしています。

 * なるべくPoorを目指すが改変の結果最悪VeryPoorになってもしかたがない
 * 服の透過対応は諦める
 * 顔は顔の皮膚テクスチャに描き込む

中にはうまかちゃんさんの紹介している方法@<bib>{umakachan}のようにメッシュを切り抜いて透過させる部分を切り抜く対応をするという方法もあります。
私も実際に一回対応してみたのですが、どうもうまく切り抜けずゴミのようなものが残ってしまいます。
なので、私は確実に対応可能な顔の対応のみ行い、服の透過は諦める感じで進めました。

//image[vanilla-vroid][最少状態のVRoidアバター][scale=0.6]{
    競泳水着：ららるーのアトリエ様
//}

この図は肌テクスチャに競泳水着@<fn>{mizugi}を重ねた状態の最小構成のVRoidアバターをVRM出力しようとしているところです。
なお、この状態でポリゴンは40,142個です。
しかも、ボーンも95個あります。
マテリアルに関しては12個もあります。
しかも、VRMの揺れものも付いている状態です。
特に、髪が長いこの子ではボーンが増えてしまわざるを得ません。
そして、この状態でそのままアップロードしてもVeryPoorにしかなりません。

//image[sorochka-vroid][ウクライナ民族衣装を着せたVRoidアバター][scale=0.6]{
    ウクライナ民族衣装：鶏肉工場様
//}

さらに、これは極端な例ですが服を着せるとこのくらいまでボーン数とテクスチャ数が増えます。
ここまで来ると最悪ボーンを削らないとアップロードできないでしょう。
ここからさらに上のランクを目指すには、Blenderとの格闘が必要になってきます。

//footnote[mizugi][競泳水着：ららるーのアトリエ様]

== アバターをBlenderで軽量化する

=== Blenderと和解せよ！

残念ながら、UnityとVRoid Studioだけではたとえ水着だとしてもQuestでまともに表示させるアバターを作るのは難しいでしょう。
ボーン数を削ることに関してはかなり難しいですが、テクスチャを重ねてポリゴンを削る所まではBlenderでなんとかできます。
なので、早速VRM出力していきましょう。
設定に関しては、デフォルトのままで大丈夫です。マテリアル数も、ボーン数も減らさなくてよいでしょう。
なぜなら、マテリアルはBlenderで結合できるからです。
ひとまず髪を短くしたアバター@<fn>{short-hair}を用意し、出力してみるとボーン数は89、これならポリゴン数を削ればFallbackにできるかもしれません。

//image[short-hair][髪を短くしてVRM出力][scale=0.6]{
    【使用衣裳】白ワンピ：星井まゆき星空通販様、スク水：ここなふぁくとりー様、桜の髪飾り：リザのアトリエ様
//}

//footnote[short-hair][【使用衣裳】白ワンピ：星井まゆき星空通販様、スク水：ここなふぁくとりー様、桜の髪飾り：リザのアトリエ様]

さて、ここからはBlenderを使うのですが、必ず2系のBlenderを使用してください。
かつ、以下のプラグインが必要になります。

 * VRM Add-on for Blender@<fn>{vrm-blender}
 * Cats Blender Plugin@<fn>{cats-blender}

//footnote[vrm-blender][https://vrm-addon-for-blender.info/ja/]
//footnote[cats-blender][https://github.com/absolute-quantum/cats-blender-plugin]

これらを使用するとVRMをBlenderで扱うことができるようになります。
まず、Blenderを開くと最初に四角形が表示されていますが、これらは消します。
その後、使用するVRMをインポートすると画面にVRMアバターが表示されます。

//image[in-blender][blenderへインポートしたところ][scale=0.6]{
//}

=== メッシュの分割

まずすべきは、CATSプラグインのModel Optionsを開き、マテリアル単位にメッシュを分割することです。
なお、1回では服のポリゴンがうまく分かれてくれないために悲惨なことになります。
顔のメッシュを分割するとシェイプキーが壊れるという話もありますが、ここは全部のメッシュを分割します。
だいたい15個前後のマテリアルになると思います。
なお、Questでは透過が使えないためここからテクスチャを編集して透過部分を削るという荒技をする人もいます。
しかし、Blenderと和解するにはかなりの時間がかかるかと思いますので今回は飛ばして先に進みます。

=== ポリゴンの削減

メッシュの分割が終わったら、Decimationのタブを開きます。
まずはCustomを選択し、全てのシェイプキーを保護します。
なお、保護しないとシェイプキーが消えて表情が付けられなくなってしまうので必ず保護しましょう。
その後にSmartを選択し、Save Fingersを選んでTrisは10,000にしてQuick Decimationをクリックします。
失敗するとロボットのように指が分離してしまうので、Save Fingersは必ず選びましょう。
そしてポリゴン数を減らすと以下のような見た目になると思います。

//image[decimated][ポリゴン数を減らしたところ][scale=0.6]{
//}

=== メッシュの結合

これが終わったらまずはメッシュを結合しましょう。
先ほどと同じCATSプラグインのModel Optionsを開くと結合できます。
これは一つにまとめてしまって大丈夫ですが、重くなるの承知でメッシュを分けると服を脱がすことができます。
ただし、重くなるのでおすすめはできません。
それと、靴下をボディスーツで着せていない場合は脱がせません。
なぜなら、肌着や普通の靴下の場合は身体のテクスチャにそのまま重なってしまうからです。
ボディスーツで靴下を着せれば脱がせられるのですが、その場合は靴に入らなくなります。
なので、脱がすギミックを仕込む場合はサンダルにして当初から靴下を履かないように作りましょう。

=== テクスチャの結合

これが終わったら、テクスチャを結合します。
まずは、Blenderのファイルを保存し、FileメニューからExternal Data内のUnpack All Into Filesを選びます。
その後に表示されるメニューではUse files in current directoryを選び、フォルダ内に保存しましょう。

//image[material][マテリアルを結合する][scale=0.6]{
//}

これが終わったらCATSプラグインのOptimizationを開き、Generate Material Listをクリックするとたくさんのテクスチャが開かれます。
Save Atlas To..をクリックするとマテリアルが結合されます。

これが終わったらEye TrackingとVisemesを設定しましょう。
これも表情に関わるところですが、次の画像の通りに設定すればよさそうです。

//image[eye-tracking][Eye Tracking（目の動き）の設定][scale=0.6]{
//}

//image[visemes][Visemes（口の動き）の設定][scale=0.6]{
//}

これが終わったらVRMに出力します。
VRMを保存し終わったらVCCとUnityの世界に帰れます。

== VCCで設定しよう

=== VCCはコマンドラインを使うとよい

この次はVCCの設定です。
実はVCCにはコマンドラインインターフェースがあります。
コマンドラインインターフェースとなるととっつきにくい印象がありますが、一度スクリプトを設定してくれるとインストールするアセットを一発で設定できるので使いやすいです。
まずは、.NET 6系をインストールします。これはVCCのコマンドラインインターフェースを使うのに必要です。
インストールしたら、次のコマンドを入力してリポジトリを追加しましょう。
ここからの内容はビデカメさんの記事に従います。

//cmd{
> @<b>{dotnet tool install --global vrchat.vpm.cli}
//}

正常にインストールできたらまずはバージョンの確認です。
次のコマンドを実行しましょう。

//cmd{
> @<b>{vpm --version}
//}

なお、アップデートは次のコマンドでできます。

//cmd{
> @<b>{dotnet tool update --global vrchat.vpm.cli}
//}

次に、テンプレートをインストールします。次のコマンドを実行してください。

//cmd{
> @<b>{vpm install templates}
//}

インストールに成功したか確かめるために、インストールされたテンプレートのリストを確認するのも忘れずに。

//cmd{
> @<b>{vpm list templates}
//}

そして、このコマンドを実行してUnity Hubが認識されているか確認しましょう。

//cmd{
> @<b>{vpm check hub}
//}

同様に、Unityも。

//cmd{
> @<b>{vpm check unity}
//}

ここが終わったら、リポジトリを追加しておきます。

//cmd{
> @<b>{vpm add repo <リポジトリのパス>}
//}

追加するリポジトリに関してですが、私は以下のリポジトリを入れています。

 * https://vpm.nadena.dev/vpm.json
 * https://mimyquality.github.io/VPM-Repository/index.json
 * https://d4rkc0d3r.github.io/vpm-repos/main.json
 * https://vpm.anatawa12.com/vpm.json
 * https://kurotu.github.io/vpm-repos/vpm.json
 * https://lilxyzw.github.io/vpm-repos/vpm.json
 * https://meronmks.github.io/vpm-repos/vpm.json
 * https://vpm.nekomimi.studio/index.json
 * https://esperecyan.github.io/VRMConverterForVRChat/registry.json
 * https://whiteflare.github.io/vpm-repos/vpm.json
 * https://vpm.ureishi.net/repos.json
 * https://mmmaellon.github.io/MMMaellonVCCListing/index.json
 * https://vpm.rerac.dev/index.json
 * https://suzuryg.github.io/vpm-repos/vpm.json

ここまでリポジトリの設定が終わったら、これらのリポジトリを一発で設定しましょう。
ファイル名は「vpm-install.ps1」として、以下の内容をコピペしておきましょう。
このスクリプトを実行すれば一発です。バージョンを上げる際にもこのスクリプトを実行すると更新してくれます。

//source[vpm-install.ps1]{
#!/usr/local/microsoft/powershell/7/pwsh

vpm add package com.vrchat.core.vpm-resolver && `
vpm add package com.vrchat.base && `
vpm add package com.vrchat.avatars && `
vpm add package dev.vrlabs.av3manager && `
vpm add package vrchat.blackstartx.gesture-manager && `
vpm add package vrchat.jordo.easyquestswitch && `
vpm add package jp.lilxyzw.liltoon && `
vpm add package jp.lilxyzw.avatar-utils && `
vpm add package nadena.dev.modular-avatar && `
vpm add package com.anatawa12.avatar-optimizer && `
vpm add package jp.pokemori.vrm-converter-for-vrchat && `
vpm add package com.github.kurotu.vrc-quest-tools && `
vpm add package jp.whiteflare.avatartools && `
vpm check project
//}

なお、PowerShellはMac用もあるのでPowerShellをインストールすればなんとMacでも動きます。
これを使えば、必要なパッケージが一発で入るという仕組みなのです。
ここでlilToonなどPC側でしか使わないアセットを入れているのに疑問を感じた方もいるかもしれません。
その理由は、PC版とUnityプロジェクトを共存させると手っ取り早く作りやすいからです。
詳しくはこのあとに記載します。

== Unityよ、私は帰ってきた！！

そしてUnityの作業です。
ここから先は慣れていることも多いと思いますので多くは語りませんが、Unityですべきことが2つあります。

=== VRMの状態で表情を設定する

まず、UnityにVRMをインポートしてそれをそのままVRChat用にコンバートしてはいけません。
なぜなら表情が設定されていないからです。
なので、Unity上でVRMに表情を指定する必要があります。
VRMアバターのBlendShapeを開き、それぞれの表情にBlendShapeを設定しましょう。
これをしないとせっかく残した表情のシェイプキーもアバターに反映されません。

//image[vrm-blendshape][VRM表情の設定][scale=0.6]{
//}

=== VRChatアバター形式にコンバートする

これが終わったらアバターをVRChatで使える形式にコンバートしましょう。
私は基本的に揺れものは全削除し、その後で設定するようにしています。
それとメッシュを分けていた人はここで要注意です。
VRMをコンバートする際にメッシュは統合されてしまいます。
それを防ぐにはNot Combine Renderer Object Namesを設定します。
これを使うことで衣服のメッシュを統合しなくてもよくなるわけです。
つまり、メニューで衣服のオンオフを設定できます。
要は、下着や水着までは脱がせるということです。
なお、ボディスーツを下着にしている場合はこれもメッシュを分けることが可能です。
しかし……そこから先はパブリックインスタンスで使いたいならやめておきましょう。
これで、コンバートすれば好きに改変できます。あとはPhysBoneを設定するなり、ギミックを仕込むなりお好きにどうぞ。

//image[vrm-convert][VRMをVRChatで使える形式にコンバートする][scale=0.6]{
//}

=== PC用とQuest用を一つのプロジェクトで使うメリット

さて、ここでlilToonを入れたことに疑問を持つ方も多いと思います。
基本的に私は様々なアバターを一つのプロジェクトに共存させています。
過去には衣装とプラットフォームごとにプロジェクトを作っていましたが、それだといちいちアセットをインストールするしかありません。
しかも、毎回表情の設定をするのは手間です。
ここでPC版とQuest版を共存させた意味が出てきます。
シェイプキーが同じであれば、FXは使い回せるのです。
これがあれば、VRMで表情を設定する手間を飛ばせます。
他のアセットも同様です。
さらには、設定のコピーもしやすいです。
なので、一つのプロジェクトでいろいろなアバターを作る方式に回帰しました。
これによって、アバター改良速度が大いに上がったと思っています。

== おわりに

以上、VRoidアバターを手っ取り早くQuest対応させる方法を紹介してきました。
設定を使い回すことに慣れれば、いろいろなバリエーションを作ることができるでしょう。
みなさんのVRChatライフがVRoid Studioでさらに豊かになることを心から祈っております。
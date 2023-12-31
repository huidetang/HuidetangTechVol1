= Unityよ、私は帰ってきた！！

そしてUnityの作業です。
ここから先は慣れていることも多いと思いますので多くは語りませんが、Unityですべきことが2つありました……が、一つは過去のものになりました。

== VRMの状態で表情を設定する（非推奨）

まず、UnityにVRMをインポートしてそれをそのままVRChat用にコンバートしてはいけません。
なぜなら表情が設定されていないからです。
なので、Unity上でVRMに表情を指定する必要があります。
VRMアバターのBlendShapeを開き、それぞれの表情にBlendShapeを設定しましょう。
これをしないとせっかく残した表情のシェイプキーもアバターに反映されません。

//image[vrm-blendshape][VRM表情の設定][scale=0.6]{
//}

なお、シェイプキーがあればVRChat形式にコンバートした後で後述するFaceEmoというツールで表情を設定することもできます。
というか、VRM形式とは別に表情を作れたり表情の合成を行ったりシェイプキーが同じ他のアバターに表情のデータを渡せたりとこっちの方が楽です。
特に、アバターに着せかえを仕込まずに衣装別にアバターを作るという場合は大活躍します。
是非ともFaceEmoを使いましょう。
FaceEmoについては後述します。

== VRChatアバター形式にコンバートする

これが終わったらアバターをVRChatで使える形式にコンバートしましょう。
私は基本的に揺れものは全削除し、その後で設定するようにしています。
それとメッシュを分けていた人はここで要注意です。メッシュを統合しないように設定する必要があります。
あとはPhysBoneを設定するなり、ギミックを仕込むなりお好きにどうぞ。

//image[vrm-convert][VRMをVRChatで使える形式にコンバートする][scale=0.8]{
//}

//embed[latex]{
\clearpage
//}

==[column] PC用とQuest用を一つのプロジェクトで使うメリット

さて、ここでlilToonを入れたことに疑問を持つ方も多いと思います。
基本的に私は様々なアバターを一つのプロジェクトに共存させています。
過去には衣装とプラットフォームごとにプロジェクトを作っていましたが、それだといちいちアセットをインストールするしかありません。
しかも、毎回表情の設定をするのは手間です。
ここでPC版とQuest版を共存させた意味が出てきます。
シェイプキーが同じであれば、FXやActionなどは使い回せるのです。
これがあれば、VRMで表情やモーションを個別に設定する手間を省けます。
他のアセットも同様です。
さらには、設定のコピーもしやすいです。
なので、一つのプロジェクトでいろいろなアバターを作る方式に回帰しました。
これによって、アバター改良速度が大いに上がったと思っています。

なお、PC版用のアバターには別のVRMファイルを用意しています。
PC版はVRoid Studioで出力したそのままのVRMファイルを使ってかまいません。
もちろん、Blenderでメッシュをあらかじめ分けておくことで、着せている服を脱がすこともできます。
Quest用にポリゴン数を減らしたものを使ってもよいのですが、顔が破綻するなど見た目がよくなくなるのでPC用はPC用で作ってしまうのがおすすめです。
さらに、PC版では透過表現も使えるので、PC版は透過にしつつQuest版では透過表現を使わないこともできるわけです。
以上のことから、同じプロジェクトでPC版とQuest版のアバターを衣装ごとに作る方が作りやすいといえるでしょう。

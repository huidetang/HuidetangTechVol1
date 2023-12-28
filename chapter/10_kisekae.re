= VRoidアバターで着せかえをする方法

VRoidは基本的に服を着替えされられない前提で組まれているので、着せかえを実装することは容易ではありません。
しかし、着せ替えもできなくはないのです。
また、他のアバターの衣装をVRoidアバターに着せたり、VRoid衣装を他のアバターに着せたりすることもできます。

なお、Android版では相当重くなるので推奨しない方法です。
PCメインの人がAndroid対応を考えるなら、水着用のFallbackアバターを作っておいてPCではPCではVery Poorなアバターを表示するという手もあります。
Android環境にも入る人については、衣装ごとにアバターは分けておくことをおすすめします。
また、衣装ごとにアバターを用意すると何かのバグで全裸でJoinしてしまったという事故も避けられます。
この事故を起こしてしまうと公式からペナルティーを受けかねないので、衣装はちゃんと着せておくことも重要です。
こういった着せ替え戦略を考えつつ、アバターの着せ替え戦略を考えておきましょう。

== ただ脱がすだけなら

VRoidアバターは重くなるの承知でメッシュを分けると服を脱がすことができます。
服のメッシュの表示と非表示を切り替えるギミックが仕込まれていれば、服を脱いで水着姿になるのは可能です。
なお、私の場合はアバターが下に着ているのはだいたい水着ですが、だいたいが趣味です。

=== VRoid Studioですること

これから述べる点に気をつければ、普通に作って問題ありません。

なお、気をつける点は下着と靴下です。
これらはボディスーツとして作らなければ、肌に直接書き込まれます。
そのため、いざ脱がそうとしても脱がせなくなってしまいます。
特に、靴下はお風呂入るときに脱ごうとしても脱げないと混乱する羽目になります。
脱がす可能性のある下着や水着、靴下はボディスーツとして作る必要があります。
なぜなら、下着や普通の靴下の場合は身体のテクスチャにそのまま重なってしまうからです。
その場合、全体を縮めておくことが重要です。
靴下や下半身の下着は「全体を縮める」を100に設定することが大事です。
それでもはみ出すときはテクスチャを消しましょう。

//image[fit-all][ボディスーツの全体を縮める][scale=0.6]{
//}

なお下着や水着の上半身はただ全体を縮めるだけだと鎖骨周りが不自然な場合があるので、その場合は適時パラメーターを調節することが必要になります。
ただし、この対策をしてしまうと服からはみ出るリスクもあるので、着せかえとはトレードオフになるリスクもありますので、どう着せるかの戦略をしっかり練っておく必要があるでしょう。

=== Blenderですること

脱がせる服のメッシュはVRM出力する前に分けたまま出力する必要があります。
メッシュは少ない方がリソースの負担は少ないですが、分かれていない場合はそもそも一部分だけを非表示にできません。
VRMをコンバートする際にメッシュは統合されてしまいます。
それを防ぐにはNot Combine Renderer Object Namesを設定します。
これを使うことで衣服のメッシュを統合しなくてもよくなるわけです。
つまり、メニューで衣服のオンオフを設定できます。
要は、下着や水着までは脱がせるということです。
なお、ボディスーツを下着にしている場合はこれもメッシュを分けることが可能です。
もちろん、何も着ていない素体をそのまま出力することもできますが、その場合にはレイティングに気をつけないと公式からきついお叱りが飛んでくるのでご注意ください。
これで、コンバートすれば好きに改変できます。

=== Unityですること

VRMを読み込んで表情の設定が終わったらVRMをVRChat形式にコンバートする必要がありますが、その際に服のメッシュを統合しない設定にしなければいけません。
VRMをVRChat形式にコンバートする際、何も設定しない場合にはメッシュを統合してしまいます。そうなるとせっかく脱がせられるようにしたのに脱げないという事態になります。
そのためには@<img>{7_vrc_essential|vrm-convert}で紹介したNot Combine Renderer Object Namesの項目で分けたメッシュを指定する必要があります。
これによって、服のメッシュを分けたまま着せ替え設定をすることができます。

その次に、そのメッシュをON/OFFできるように設定をする必要があります。
ギミックの設定のところで紹介したAvatarMenuCreater for Modular Avatarを使って、服のメッシュをオンオフできるように設定します。
これで動作を確認すると、VRoidアバターで服の着せかえができるようになります。

== Modular Avatarを使って複数のアバターを着せ替える

で、これまでは1種類の服を着せ替えることしかできませんでした。
しかし、Modular Avatarの力を借りれば、衣装さえ用意できれば着せかえができるということになります。
これに関しては@<bib>{no-rashomon>}で紹介されている方法を持ちいるとうまくいくでしょう。
そのためには、同じ素体の衣装出力用VRMをもう一個作ってしまえばよいのです。
どうせ他のメッシュは消すので、ボーンを節約するために髪の毛はない方がよいでしょう。

//image[hage][衣装出力用のアバター][scale=0.6]{
//}

で、これも普通のアバター同様にBlenderでボーンの最適化をして再度VRMに出力しておきます。
目や口の設定については不要です。どうせ消すので。
もちろん、服のメッシュを分けておかないと服として使えなくなるのでそこはお忘れなきように。

で、UnityでこのVRMを取り込んだら、まずすべきは衣装以外のメッシュを消します。
その時活躍するのがMeshDeleterWithTexture@<fn>{mesh-deleter}です。
これで、服以外のメッシュをすべて消すと、服だけのPrefabが出来上がります。
なお、ボーンは現時点では敢えて消していません。
この際に、間違えてウェイトの乗っているボーンを消すと愉快なことになるのでご注意ください。

//image[hashira][ウェイトの乗っているボーンを消してしまって愉快なことになった例]{
//}

ただ、ボーンが多ければアバターに統合するのも難しくなってしまいます。
なにせ、Modular Avatarのオブジェクト数の上限は255個なので、それ以上オブジェクトが多くなるとこれ以上合成できなくなってしまうのです。
なので、いろいろと衣装を着せる際にはボーンを削る必要がありそうです。

//footnote[mesh-deleter][https://booth.pm/ja/items/1501527]
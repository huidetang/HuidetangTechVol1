= 手っ取り早くVRoidアバターをQuest対応させる方法

== はじめに

私がVRChatにいるとき、だいたいVRoid Studioで作成したアバターを使っています。
私はVRChatにはPC版から入りましたが、初めて入ったのがQuestユーザーのイベントだったので早い段階でアバターのQuest対応を意識しています。
しかし、VRChatのQuest版ではシェーダーが限定され、透過が使えないなどの厳しい制限があります。
他のアバターならポリゴン数を削れば何とかなるのですが、VRoid製アバターの場合テクスチャに透過をかなり多く使っているため対応にコツがいります。
しかしながら、大体これならちょうどよいという改変方法を見つけたので共有します。
既出だったり、手ぬるいと言われたりするかもしれませんが、ご笑納いただければ幸いです。

== Questアバターへの制限

VRChatのQuest版やAndroid版でアバターを使うには以下のような制限があります。
まずはじめに、VRChat公式ではQuestで使用するアバターはポリゴン数を10,000以下にすることを推奨@<bib>{VRCQuest}しています。
そして、VRChatのアバターは表示のしやすさに応じてランクが付けられています。
非常に軽くて表示しやすいExcellentのアバターを作るのはよほど単純化しないといけません。
ランクがExcellentやGoodならQuestで表示できないアバターを使っているときに表示するFallbackアバターにすることができますが、多くのアバターはPoorかVeryPoorになってしまうと思います。
イベントによっては重くなるのでVeryPoorのアバターを使っている人の参加をお断りすることがあり、PoorランクやMediumランクを目指す改変者も多いです。

で、公式の情報@<bib>{VRCPerformanceRanks}によれば、Quest版アバターのランク付けについては以下の通りとなっています。

//image[QuestAvatarRank][Quest版アバターのランク付け]{
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

//image[vanilla-vroid][最少状態のVRoidアバター][scale=0.8]{
    競泳水着：ららるーのアトリエ様
//}

この図は肌テクスチャに競泳水着@<fn>{mizugi}を重ねた状態の最小構成のVRoidアバターをVRM出力しようとしているところです。
なお、この状態でポリゴンは40,142個です。
しかも、ボーンも95個あります。
マテリアルに関しては12個もあります。
しかも、VRMの揺れものも付いている状態です。
この状態でそのままアップロードしてもVeryPoorにしかなりません。

//image[sorochka-vroid][ウクライナ民族衣装を着せたVRoidアバター][scale=0.8]{
    ウクライナ民族衣装：鶏肉工場様
//}

さらに、これは極端な例ですが服を着せるとこのくらいまでボーン数とテクスチャ数が増えます。
ここまで来ると最悪ボーンを削らないとアップロードできないでしょう。
ここからさらに上のランクを目指すには、Blenderとの格闘が必要になってきます。

//footnote[mizugi][競泳水着：ららるーのアトリエ様]

== アバターをBlenderでごにょごにょする

残念ながら、UnityとVRoid Studioだけではたとえ水着だとしてもQuestでまともに表示させるアバターを作るのは難しいでしょう。
ボーン数を削ることに関してはかなり難しいですが、テクスチャを重ねてポリゴンを削る所まではBlenderでなんとかできます。
なので、早速VRM出力していきましょう。


= 手っ取り早くVRoidアバターをQuest対応させる方法

== はじめに

私はVRChatにはPC版から入りましたが、初めて入ったのがQuestユーザーのイベントだったので早い段階でアバターのQuest対応を意識しています。

しかし、VRChatのQuest版ではシェーダーが限定され、透過が使えないなどの厳しい制限があります。
他のアバターならポリゴン数を削れば何とかなるのですが、VRoidの場合テクスチャに透過をかなり多く使っているため対応にコツがいります。
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

//table[QuestRank][Quest版VRChatのアバターランク]{
Avatar Quality	Excellent	Good	Medium	Poor
-------------------------------------------------------------------------------------
Polygons	7,500	10,000	15,000	20,000
Bounds Size1	2.5m x 2.5m x 2.5m	4m x 4m x 4m	5m x 6m x 5m	5m x 6m x 5m
Texture Memory	10 MB	18 MB	25 MB	40 MB
Skinned Meshes	1	1	2	2
Meshes	1	1	2	2
Material Slots	1	1	2	4
Animators	1	1	1	2
Bones	75	90	150	150
PhysBones @<br>{} Components2	0	4	6	8
PhysBones @<br>{} Affected Transforms2	0	16	32	64
PhysBones @<br>{} Colliders2	0	4	8	16
PhysBones @<br>{} Collision Check Count2	0	16	32	64
Avatar Dynamics @<br>{} Contacts2	2	4	8	16
Particle Systems	0	0	0	2
Total Particles @<br>{} Active	0	0	0	200
Mesh Particle @<br>{} Active Polys	0	0	0	400
Particle Trails @<br>{} Enabled	False	False	False	True
Particle Collision @<br>{} Enabled	False	False	False	True
Trail Renderers	0	0	0	1
Line Renderers	0	0	0	1
//}

なお、Quest版で初期状態で見えるランクはMediumであり、使っているアバターがMediumランクに対応していればQuestの人から初期状態で見えることになります。
しかし、Mediumランクでさえこれを実現するのは難しいです。
ましてや、Fallbackアバターを目指すのは至難の業と言うことがお分かりでしょう。

== 改変方針

私はQuest対応アバターを作る時、以下のような改変方針にしています。

 * 改変の結果最悪VeryPoorになってもしかたがない
 * 服の透過対応は諦める
 * 顔は顔の皮膚テクスチャに描き込む


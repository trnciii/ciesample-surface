この章は 第2回 相対移動 の内容に対応しています。
[このリポジトリ](https://github.com/trnciii/ciesample-surface)からファイルをダウンロードしたら`sample.xcodeproj` を開き、実行できるか確認してください。



## 目次
* [準備](#準備)
* [プログラムの説明](#プログラムの説明)
	* [描画内容](#描画内容)
	* [図形のタイプ](#図形のタイプ)
	* [再描画](#再描画)
* [課題1](#課題1)
* [ディスプレイリスト](#ディスプレイリスト)
* [移動・回転・拡大縮小](#移動-回転-拡大縮小)
* [課題2](#課題2)
* [行列の初期化](#行列の初期化)
* [課題3](#課題3)


## 準備
ここのコードをダウンロード、解凍してください。sample.xcodeproj を開き実行すると、中央に白い四角形が現れるはずです。	


## プログラムの説明
初期化処理については[直線の回](https://github.com/trnciii/cge2020mac/tree/1_lines)を参考にしてください。


### 描画内容
次のdisplay関数では、四角形を描いています。
```cpp
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f( 0.5f, 0.5f);
        glVertex2f( 0.5f,-0.5f);
        glVertex2f(-0.5f,-0.5f);
    glEnd();
}
```
`glColor3f(); `ではこれから描く頂点の色を設定しています。括弧内の値は左から赤、緑、青の強さで、それぞれ0.0～1.0 の値をとります。ここでは全ての値が1 ですので、色は白になります。

`glVertex2f();` は頂点を設定していて、括弧内の数字は点の座標です。
この場合、４つの点が定義されています。 そして、これらをどのようにしてつないでいくかというのが`glBegin();`の括弧内の文字列で示されています。 この場合は`GL_POLYGON`となっていますから、４つの頂点で一枚のポリゴン（面）が作られています。 そして、`glEnd();`で定義を終わります。

### 図形のタイプ

`glBegin();` の括弧内の`GL_POLYGON` 部分を書き換えることにより、図形のタイプを指定することができます。

|タイプ名								|説明										|
|-----------------------------------|-------------------------------------------|
|GL_POINTS							|点を打ちます									|
|GL_LINES							|２点を対にして、その間を直線で結びます。			|
|GL_LINE_STRIP						|折れ線を描きます。								|
|GL_LINE_LOOP						|折れ線を描きます。始点と終点の間も結ばれます。		|
|GL_TRIANGLES / GL_QUADS			|３／４点を組にして、三角形／四角形を描きます。		|
|GL_TRIANGLE_STRIP / GL_QUAD_STRIP	|一辺を共有しながら帯状に三角形／四角形を描きます。	|
|GL_TRIANGLE_FAN					|一辺を共有しながら扇状に三角形を描きます。			|
|GL_POLYGON							|凸多角形を描きます。							|

### 再描画
次の関数は「再描画」のための関数です。ここで視界の設定をしています。以下で説明していない部分に付いては、後の章で説明します。

```cpp
void reshape(GLFWwindow* window, int w, int h)
{
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h );　//ウィンドウ全体をビューポートにする
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);　//視野の指定
}
```
`glOrtho();`では視界の設定をしています。
括弧内左から、ウィンドウ左端、右端、上、下、そして手前、奥の座標を設定し、この範囲内にある物体を描画するようにしています。図にすると下のようになります。<br>
`glOrtho(left, right, bottom, top, near, far);`のとき

![](http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cge2020/img/surface/viewport1.jpg)

この「視野の範囲」は３次元であり、視体積と呼びます。


## 課題1
あなたのイニシャルを、画面上に描いてください。"MP1”だとイメージとしては下のようなものになります。

![](http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cge2020/img/surface/MP1.gif)

## ディスプレイリスト
ディスプレイリストを使うと、図形を描く、などの命令を保存し、それを簡単に呼び出したりすることができます。つまり、一度定義した物体を「使い回す」事ができます。
では まず、プログラムの頭部分に次の黒文字の行を書き加えてください。
```cpp
#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"
#include <math.h>

#define SQUARE 1
```
`#define` はある文字列を違う文字列に置き換える定義をします。ここでは、「"SQUARE "という文字列を数字の1と等しいとみなす」という処理を行っています。これを"マクロ定義（マクロ置き換え）"と言います。

続いて、`myinit()` の中を次のように書き換えて下さい。
```cpp
void myinit(GLFWwindow** window)
{
    glfwInit();
    *window = glfwCreateWindow(600, 600, "surface", NULL, NULL);
    glfwMakeContextCurrent(*window);
    glClearColor(0, 0, 0, 1);
    
    // ここから追記
    glNewList(SQUARE, GL_COMPILE);

    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f( 0.5f, 0.5f);
        glVertex2f( 0.5f,-0.5f);
        glVertex2f(-0.5f,-0.5f);
    glEnd();

    glEndList();
    // 追記おわり
}
```
`glNewList()` は保存を開始します。 `glEndList()` は保存を終了します。
つまり、この二つの間に書かれた処理を保存することになります。

この場合、“四角を描く”という命令が保存されることになります。
この場合、SQUARE（つまり"1"）に"四角を描く"という命令を保存したことになります。

定義したオブジェクトを使ってみましょう。`display()` の中を次のように書き換えます。
```cpp
void display(void){

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glColor3f(1.0f, 1.0f, 1.0f);
	glCallList(SQUARE);	
	glFlush();
}
```
リストで定義されたオブジェクトの呼び出しには、 `glCallList()` を使います。括弧内（引数）はオブジェクトの名前（整数）が入ります。ここではSQUARE（=1）という名前のオブジェクト＝先ほどリストで定義したオブジェクトを呼び出しています。
実行してみても見かけは変わりません。でも、複雑なオブジェクト（ここでは単なる正方形ですが・・・）を１行の記述で呼び出すことができます。


## 移動 回転 拡大縮小
物体を移動・回転・拡大縮小するためには、以下のような関数を利用します。

|操作|関数|例|
|:-:|:-|:-|
|移動|`glTranslatef(x方向の移動量, y方向の移動量, z方向の移動量)`|glTranslatef(0.0, 10.0, 0.0) → y方向に10.0だけ移動|
|回転|`glRotatef(回転角度, 回転軸x, 回転軸y, 回転軸z)`|glRotatef(30.0, 0.0, 0.0, 1.0) → z軸中心に30.0度回転|
|拡大縮小|`glScalef(x方向の拡大率, y方向の拡大率, z方向の拡大率)`|glScalef(1.0, 2.0, 1.0) → y方向にだけ2倍の大きさにする|

OpenGLでは物体の移動・回転・拡大縮小を行うときには、**行列の演算**を使います。これらの変換の関数を使うごとに、現在の行列にその変換行列が乗算されていきます。これらを使う場合物体の描画の前に記述しますが、計算は物体の描画に近い **"下から 順番に"** 行われます。また、 **一度書いた関数はそのあとの変換にもずっと影響します**。

例えば、
```cpp
glRotatef(回転度数, x軸中心, y軸中心, z軸中心); // 回転行列R
glTranslatef(x方向移動, y方向移動, z方向移動); // 移動行列T
glCallList(SQUARE); // 定義されているオブジェクトを呼び出し
```
は R\*T という行列演算をしてからそれをオブジェクトの頂点ベクトルvに(左側から)かけていることになります。<br>
つまり、描画される座標 = R\*T\*v です。

このとき、変換はオブジェクトの記述に近い側からなされるということに気をつけてください。
上の例では、移動T後、回転Rを行っていることになります。
イメージとしては下の図のようになります。

![](http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cge2020/img/surface/matrix.png)

## 課題2
次のような画面を作ってみて下さい。

![](http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cie2022/img/surface/1_2_var0.gif)

## 行列の初期化
このようにどんどん変換が積み重なっていく仕組みでは、一度書いた変換がそのあと全ての変換に影響するので直感的に操作しにくい場合があります。これを解消するため、必要に応じて行列を初期化することができます。

`glLoadIdentity()`を使うことで行列を初期化し、それまで使われた変換行列が、この関数以降には全く影響しなくなります。

## 課題3
次のような画面を作ってみて下さい。

<img src="http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cie2022/img/surface/ogl1_4.gif" width="300"> <img src="http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cie2022/img/surface/square2.gif" width="300"><br>

<img src="http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cie2022/img/surface/1_2_var1.gif" width="300"> <img src="http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cie2022/img/surface/1_2_var2.gif" width="300">

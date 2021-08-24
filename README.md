# IcEscape
| ![](./img/1.png) | ![](./img/2.png) |
| ---------------- | ---------------- |
| ![](./img/3.png) | ![](./img/4.png) |

### 한국게임과학고등학교 2학년 팀프로젝트

프로젝트 소개 : IcEscape는 지구온난화에 대한 경각심을 일깨우는 내용을 담고 있는 헥사형 블록퍼즐 게임입니다.

사용 기술 : 

C++, EM엔진(한국게임과학고등학교 교내엔진)

C++ , Cocos2d-x

C#, Xna(with cocos2d-x)

> EM엔진으로 제작이후 EM엔진의 몇가지 한계를 절감하고 Cocos2d-x 엔진으로 포팅
>
> 이후 WindowsPhone7 버전을 제작하기 위해 C#, XNA로 포팅

담당 역할 : 팀장, 프로그래밍 전체

개발기간 : 2012년 6월~ 2012년 11월

핵심 기술 / 알고리즘 : 블록 생성 및 제거 시스템. 블록 움직이기와 터트리기. 파티클 시스템.

게임 소개 : Gitbug-게임소개 및 발표자료 폴더를 참고해주세요.

플레이 영상 : https://youtu.be/zxegM73VGtI

프로젝트 주소 : https://github.com/justkoi/IcEscape

### 핵심 코드 설명

#### GameScene.cpp : 게임 메인 씬으로서 블록 생성 및 제거. 블록 이동 및 드래그하여 터트리는 알고리즘을 주관합니다.

CreateBlock

ccTouchBegan

ccTouchMoved

ccTouchEnded

#### Block.cpp : 블록에 대한 업데이트를 주관합니다.

의의 : cocos2d-x 를 사용하여 게임엔진에 대한 이해. tocuh began, move, end를 통해 터치 시스템에 대한 이해, STL list, vector를 iterator를 사용하여 순회.

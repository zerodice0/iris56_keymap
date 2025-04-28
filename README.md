# IRIS 키보드 키맵 세팅
기본 키맵을 기반으로 macOS에서 사용하기 편하도록 추가적인 키를 할당해놓은 펌웨어 레포지터리입니다.

## IRIS 키보드 소개
![IRIS 키보드](https://keeb.io/cdn/shop/files/keyset-iris_1100x_8dba1734-1572-455b-aab2-1380992644e1.png?height=714&v=1707776710&width=952)
Iris는 손을 더 자연스러운 위치에 놓을 수 있도록 도와주는 Keebio의 가장 인기 있는 스플릿 키보드입니다. 수천 명의 사용자들이 Iris를 통해 반복성 스트레스 손상(RSI), 손목 터널 증후군, 과운동성(hypermobility) 등의 문제를 개선했습니다.
Iris는 다양한 버전으로 제공되어, 사용자 개개인의 필요에 완벽하게 맞는 스타일을 선택할 수 있습니다.

[KEEB.IO](https://keeb.io/collections/all/products/iris)에서 보드와 키캡, 상하판을 비롯한 부품을 구매할 수 있습니다. $150를 넘어가게되면 관세를 지불해야 할 수 있으므로, 보드와 상하판 등 필수적인 부품만 KEEB.IO에서 구매하고 키캡과 스위치는 알리익스프레스 등에서 구매하는 것을 추천합니다.

#### KEEB.IO에서 주문해야하는 부품
- PCB 보드
- 알류미늄 상/하판(플레이트 킷)
- 미들 레이어 (옵션, 없어도 되긴 함)

#### 알리익스프레스/다이소 등에서 주문해도 되는 부품
- 키캡
- 스위치
- 미끄럼 방지용 고무패드
- 키보드 링크 케이블(C to C)

## 기본적인 키맵 세팅
#### QMK Configurator
[QMK Configurator](https://config.qmk.fm/#/keebio/iris/rev7/LAYOUT)에서 간단한 키보드 설정이 가능합니다.

#### VIA 
PCB 보드에 기본적으로 설치되어있는 rules.mk에는 `VIA_ENABLE` 옵션이 `FALSE` 설정되어있습니다. 따라서 VIA를 사용하기 위해서는 [VIA Firmware](https://caniusevia.com/docs/download_firmware/)에서 보드에 맞는 펌웨어를 다운받아 설치해야 VIA를 사용한 키 설정이 가능합니다.

## 키맵 설정 및 QMK Firmware 빌드
[QMK Firmware](https://github.com/qmk/qmk_firmware) 레포지터리에서 키맵 설정 및 QMK Firmware 빌드 방법을 설명합니다. `keymap.c` 파일을 수정하여 키 할당을 변경하고, `rule.mk` 파일을 수정해서 설정을 변경합니다. PCB 보드에 기본적으로 설치되어있는 펌웨어에는 마우스 키를 사용하기 위한 `MOUSEKEY_ENABLE` 옵션이나 VIA를 사용하기 위한 `VIA_ENABLE` 옵션이 설정되어있지 않습니다. 따라서 보다 자신에게 맞는 사용방법을 익히기 위해서는 QMK Firmware를 사용해서 펌웨어 빌드 방법을 익히는 것이 좋습니다.

## 이 레포지터리를 통해 배포되는 펌웨어는?
저는 주로 MacOS 환경에서 키보드 펌웨어를 빌드하고 사용합니다. 따라서 Windows/Linux 환경에서 키보드를 사용하는 경우에는 마우스 휠 스크롤이 반대라던지, 일부 단축키가 다른 문제가 발생할 소지가 있습니다. 이 점을 참고해주세요.

기본적으로는 PCB 보드에 설치되어있는 기본 키맵을 따르며, 추가적으로 단축키를 할당했습니다.
1. HOME 대신 FN3 할당
2. END 대신 CMD+OPT(ALT) 키 할당
3. FN1 + FN2 + 6으로 미션 컨트롤 실행
4. FN1 + FN2 + 7로 런치패드 실행
5. FN3 + H,J,K,L 로 마우스 커서 이동
6. FN3 + N,M,<,> 로 마우스 휠 스크롤
7. FN3 + Y,U,I,O 로 마우스 버튼 클릭
8. FN3 + P, DEL 로 CHROME 이전 페이지/다음 페이지로 이동
9. FN3 + ;, '로 FINDER 상위 폴더/하위 폴더로 이동
10. FN3 + 6 으로 일부 영역 스크린 캡쳐
11. FN3 + 7 으로 일부 영역 스크린 캡쳐 후 복사
12. FN3 + 8 으로 전체 화면 스크린 캡쳐
13. FN3 + 9 으로 전체 화면 스크린 캡쳐 후 복사

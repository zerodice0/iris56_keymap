# IRIS 키보드 zerodice0 키맵 세팅
기본 키맵을 기반으로 추가적인 키를 할당해놓은 펌웨어 레포지터리입니다.

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
이 펌웨어는 **macOS, Windows, Linux, iOS**를 지원하며 키보드 단축키가 자동으로 적응합니다. 펌웨어가 자동으로 운영체제를 감지하여 스크린샷 캡처, 언어 전환, 마우스 휠 방향에 적절한 단축키를 적용합니다.

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
10. OS에 독립적인 스크린샷 단축키 (OS에 자동 적응):
    - **SC_FULL** (FN3+8): 전체 화면 캡쳐
    - **SC_AREA** (FN3+6): 영역 선택 캡쳐
    - **SC_MENU** (FN3+9): 스크린샷 메뉴/옵션
    - **SC_CLIP_FULL** (FN3+Shift+8): 클립보드로 전체 화면 캡쳐
    - **SC_CLIP_AREA** (FN3+7): 클립보드로 영역 선택 캡쳐
11. **LANG_SW** (FN1 + 오른쪽 하단)로 언어 전환: OS 입력 방식에 자동 적응
12. 마우스 휠 방향 (**MW_RIGHT/UP/DOWN/LEFT**) OS별 자동 조정

## 멀티 OS 호환성

이 펌웨어는 운영체제(macOS, Windows, Linux, iOS)를 자동으로 감지하여 키보드 단축키를 적용하는 OS 인식 기능을 구현했습니다.

### OS별 지원 기능

| 기능 | macOS/iOS | Windows | Linux |
|------|-----------|---------|-------|
| 스크린샷 단축키 | ✅ 완전 지원 (Cmd+Shift+3/4/5) | ✅ 캡처 도구 (Win+Shift+S) | ✅ PrtScn 변형 |
| 언어 전환 | ✅ Ctrl+Space / Caps Lock | ✅ Right Alt | ✅ Shift+Space |
| 마우스 휠 방향 | ✅ 자연스러운 스크롤 | ✅ 역방향 스크롤 | ✅ 역방향 스크롤 |
| 마우스 제어 | ✅ 완전 지원 | ✅ 완전 지원 | ✅ 완전 지원 |

### OS별 단축키 상세

#### 스크린샷 키코드
- **SC_FULL**: 전체 화면 캡쳐
  - macOS: Cmd+Shift+3
  - Windows: Win+Shift+S (캡처 도구)
  - Linux: PrtScn

- **SC_AREA**: 영역 선택
  - macOS: Cmd+Shift+4
  - Windows: Win+Shift+S
  - Linux: Shift+PrtScn

- **SC_MENU**: 스크린샷 메뉴/옵션
  - macOS: Cmd+Shift+5 (스크린샷 메뉴)
  - Windows: Win+Shift+S
  - Linux: PrtScn

- **SC_CLIP_FULL**: 클립보드로 전체 화면 캡쳐
  - macOS: Cmd+Ctrl+Shift+3
  - Windows: Win+Shift+S (클립보드에 저장)
  - Linux: Ctrl+PrtScn

- **SC_CLIP_AREA**: 클립보드로 영역 선택 캡쳐
  - macOS: Cmd+Ctrl+Shift+4
  - Windows: Win+Shift+S
  - Linux: Ctrl+Shift+PrtScn

#### 언어 전환
- **LANG_SW**: OS 인식 언어/입력 소스 전환
  - macOS: Ctrl+Space
  - iOS: Caps Lock
  - Windows: Right Alt (언어 표시줄)
  - Linux: Shift+Space (IBus/Fcitx)

#### 마우스 휠 방향
- **MW_RIGHT/UP/DOWN/LEFT**: OS 스크롤 규칙에 자동 적응
  - macOS/iOS: 자연스러운 스크롤 (휠 오른쪽 = 스크롤 오른쪽)
  - Windows/Linux: 역방향 스크롤 (휠 오른쪽 = 스크롤 왼쪽)

### 동작 원리

펌웨어가 키보드를 연결할 때 자동으로 OS를 감지하여 올바른 단축키를 적용합니다. OS 감지를 사용할 수 없는 경우 펌웨어는 기본적으로 macOS 단축키를 사용합니다. 모든 단축키는 연속 키 입력을 지원합니다 - 키를 꾹 누르면 동작이 반복됩니다 (마우스 휠 스크롤의 가속도 지원에 유용).

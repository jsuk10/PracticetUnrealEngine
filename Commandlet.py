import os
import subprocess
from pathlib import Path
from typing import Optional

# ===== 공용 유틸 =====
def _message_box(title: str, message: str) -> None:
    """Windows 메시지 박스. 실패 시 콘솔로 대체."""
    try:
        import ctypes
        ctypes.windll.user32.MessageBoxW(0, message, title, 0x10)  # MB_ICONHAND
    except Exception:
        print(f"[POPUP] {title}: {message}")

def _first_uproject_in(directory: Path) -> Optional[Path]:
    """지정 폴더에서 첫 번째 .uproject 반환."""
    matches = list(directory.glob("*.uproject"))
    return matches[0] if matches else None

def _pick_ue4_editor(bin_dir: Path) -> Optional[Path]:
    """Cmd 우선 선택, 없으면 GUI 에디터 반환."""
    cmd = bin_dir / "UE4Editor-Cmd.exe"
    if cmd.exists():
        return cmd
    gui = bin_dir / "UE4Editor.exe"
    if gui.exists():
        return gui
    return None

# ===== 핵심 실행기 =====
def run_commandlet(
    commandlet_name: str,
    args: list[str] | None = None,
    extra_env: dict[str, str] | None = None,
) -> int:
    """
    현재 작업 디렉터리의 한 단계 상위 폴더에서:
    - .uproject 탐색
    - ue4\\Engine\\Binaries\\Win64 하위에서 UE4Editor(-Cmd).exe 탐색
    을 수행해 커멘드릿을 실행하고 출력 스트리밍.
    """
    current = Path.cwd()
    parent = current.parent

    # 1) 부모 폴더에서 .uproject 찾기
    uproject = _first_uproject_in(current)
    if not uproject:
        _message_box("UPROJECT 없음", f".uproject 파일을 찾을 수 없습니다.\n검색 경로: {current}")
        raise FileNotFoundError(f".uproject not found in {current}")

    # 2) 부모 폴더에서 ue4\\Engine\\Binaries\\Win64 지정
    ue4_bin_dir = Path(os.path.join(str(parent),"ue4","Engine","Binaries","Win64"))
    if not ue4_bin_dir.exists():
        _message_box("UE4 BIN 폴더 없음", f"UE4 BIN 폴더가 없습니다.\n기대 경로: {ue4_bin_dir}")
        raise FileNotFoundError(f"UE4 bin not found: {ue4_bin_dir}")

    # 3) 실행 파일 선택: UE4Editor-Cmd.exe → UE4Editor.exe
    ue4_exec = _pick_ue4_editor(ue4_bin_dir)
    if not ue4_exec:
        _message_box(
            "UE4 실행 파일 없음",
            f"UE4Editor-Cmd.exe 또는 UE4Editor.exe가 없습니다.\n경로: {ue4_bin_dir}"
        )
        raise FileNotFoundError(f"No UE4 editor executable in {ue4_bin_dir}")

    # 4) 명령 구성 및 실행
    cmd = [str(ue4_exec), str(uproject), f"-run={commandlet_name}"]
    if args:
        cmd.extend(args)

    env = os.environ.copy()
    if extra_env:
        env.update(extra_env)
    
    print("cmd : ", cmd)

    proc = subprocess.Popen(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        encoding="utf-8",
        errors="replace",
        env=env,
    )

    assert proc.stdout is not None
    for line in proc.stdout:
        print(line, end="")

    code = proc.wait()
    print(f"\n[UE4 Commandlet ExitCode] {code}")
    return code


if __name__ == "__main__":
    # 예시
    COMMANDLET = "TestCommandlet"
    ARGS = ["-Key=Value", "Foo", "Bar"]
    run_commandlet(COMMANDLET, ARGS)

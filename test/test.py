from difflib import Differ
from subprocess import run, PIPE, STDOUT
from pathlib import Path
import sys

MD = """**REFERENCIA**

```diff
- Línea esperada
+ Línea obtenida
```

**RESULTADOS**

{results}**RESUMEN**

| | Cantidad | Porcentaje |
|-|-|-|
| Éxito | {success} | {successp:.2%} |
| Error | {error} | {errorp:.2%} |
| N/T | {nt} | {ntp:.2%} |
| **Total** | **{total}** | **100.00%** |
"""

WARN = ":warning: **AVISO**"
SUCCESS = ":heavy_check_mark: **ÉXITO**"
ERROR = ":x: **ERROR**"
RESULT = "{type}: (`{file}{ret}`) {desc}{diff}\n\n"
RETURN = " = {code}"
DIFF = "\n\n```diff\n{diff}```"


def get_expected_from_file(source_path, suffix=".out"):
    try:
        with open(source_path.with_suffix(suffix), encoding="utf8") as f:
            return f.read()
    except FileNotFoundError:
        return ""


def get_expected_from_comments(source_file, prefix):
    expected = ""
    i = len(prefix)
    for line in source_file.readlines():
        if line.startswith(prefix):
            expected += line[i:]
    return expected


def get_diff(differ: Differ, expected: str, actual: str):
    dif = differ.compare(expected.splitlines(True), actual.splitlines(True))
    r = ""
    for line in dif:
        code = line[:2]
        if code == "  ":
            # Omite líneas correctas
            continue
        r += line
    return r


def main():
    test_dir_abs_path = Path(__file__).parent.resolve()
    aleph_dir_abs_path = test_dir_abs_path.parent
    # Agrega la carpeta del ejecutable al "path"
    sys.path.append(str(aleph_dir_abs_path))
    success = 0
    error = 0
    nt = 0
    d = Differ()
    test_dir_abs_path = sorted(test_dir_abs_path.glob("**/*.a"))
    results = ""
    for test_file_abs_path in test_dir_abs_path:
        dir_file_name = f"{test_file_abs_path.parent.name}/{test_file_abs_path.name}"
        rel_path = test_file_abs_path.relative_to(aleph_dir_abs_path).as_posix()
        expected = get_expected_from_file(test_file_abs_path)
        with open(test_file_abs_path, encoding="utf8") as f:
            description = f.readline().rstrip()[3:]
            if not expected:
                expected = get_expected_from_comments(f, "///")
            else:
                expected += "\n" if expected[-1] != "\n" else ""
        if not expected:
            results += RESULT.format(
                type=WARN,
                file=dir_file_name,
                desc="No se definió una salida esperada",
                ret="",
                diff="",
            )
            nt += 1
            continue
        res = run(["./aleph", "-c", rel_path], stdout=PIPE, stderr=STDOUT, text=True)
        if res.stdout == expected and res.returncode == 0:
            success += 1
            results += RESULT.format(
                type=SUCCESS, file=dir_file_name, desc=description, ret="", diff=""
            )
        else:
            error += 1
            results += RESULT.format(
                type=ERROR,
                file=dir_file_name,
                desc=description,
                ret=RETURN.format(code=res.returncode) if res.returncode != 0 else "",
                diff=DIFF.format(diff=get_diff(d, expected, res.stdout)),
            )
    total = success + error + nt
    md = MD.format(
        results=results,
        success=success,
        error=error,
        nt=nt,
        successp=success / total,
        errorp=error / total,
        ntp=nt / total,
        total=total,
    )
    print(md)
    if error > 0:
        exit(1)


if __name__ == "__main__":
    main()

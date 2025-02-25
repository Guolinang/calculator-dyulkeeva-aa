import subprocess

def test_math1():
    res=subprocess.run(["build/app.exe", "--float"], input="(125*2314-(231-(123*8)+(((16*8)-97)/12)))/3",text=True,capture_output=True)
    assert res.returncode == 0
    assert (abs(float(res.stdout)-96666.80556)<10**(-4))


def test_math2():
    res=subprocess.run(["build/app.exe", "--float"], input="  (  3 + 4 )  * 2", text=True,capture_output=True)
    assert res.returncode == 0
    assert (abs(float(res.stdout)-14)<10**(-4))


def test_tab1():
    res=subprocess.run(["build/app.exe", "--float"], input="\t9\n-\n5",text=True,capture_output=True)
    assert res.returncode == 0
    assert (abs(float(res.stdout)-4)<10**(-4))

def test_tab2():
    res=subprocess.run(["build/app.exe", "--float"], input="((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((2+1+(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((2*4)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))",text=True,capture_output=True)
    assert res.returncode == 0
    assert (abs(float(res.stdout)-11)<10**(-4))


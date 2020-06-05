project('cryptopals', 'c')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

incdir = include_directories('src')

executable('ex01', ['src/ex01/main.c', 'src/utils.c'], dependencies: m_dep, include_directories: incdir)
executable('ex02', ['src/ex02/main.c', 'src/utils.c'], dependencies: m_dep, include_directories: incdir)
executable('ex03', ['src/ex03/main.c', 'src/utils.c'], dependencies: m_dep, include_directories: incdir)
executable('ex04', ['src/ex04/main.c', 'src/utils.c'], dependencies: m_dep, include_directories: incdir)
executable('ex05', ['src/ex05/main.c', 'src/utils.c'], dependencies: m_dep, include_directories: incdir)
executable('ex06', ['src/ex06/main.c', 'src/utils.c'], dependencies: m_dep, include_directories: incdir)

munit_dep = dependency('munit', fallback: ['munit', 'munit_dep'])

tests = executable('tests', ['tests/main.c', 'src/utils.c'], include_directories: incdir,
		   dependencies: [m_dep, munit_dep])
test('tests', tests)

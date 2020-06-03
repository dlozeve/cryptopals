project('cryptopals', 'c')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

executable('ex01', ['ex01/main.c', 'utils.c'], dependencies: m_dep)
executable('ex02', ['ex02/main.c', 'utils.c'], dependencies: m_dep)
executable('ex03', ['ex03/main.c', 'utils.c'], dependencies: m_dep)
executable('ex04', ['ex04/main.c', 'utils.c'], dependencies: m_dep)

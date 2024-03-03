# SConstruct
import os

###########################################################
# FLAGS for Compilation
###########################################################

cflags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-std=c99',
    '-Wno-discarded-qualifiers',
    '-Wno-unused-variable',
    '-Wno-unused-parameter',
    '-Wpointer-arith',
]

env = Environment(
    ENV={ 'PATH': os.environ['PATH'] },
    CC='gcc',
    CCFLAGS=cflags,
    CPPPATH=[],
    LIBS=[],
)

###########################################################
# Action Functions
###########################################################

def clang_format(target, source, env):
    return env.Execute("clang-format i $SOURCE")

COMMAND = COMMAND_LINE_TARGETS[0] if COMMAND_LINE_TARGETS else ""

if COMMAND == "clean":
    AlwaysBuild(Command('#/clean', [], 'rm -rf build/*'))

elif COMMAND == "format":
    SConscript('scons/format.scons', exports={'env': env})
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
    '-Isrc',
    '-Iinc'
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
    return env.Execute('clang-format i $SOURCE')

COMMAND = COMMAND_LINE_TARGETS[0] if COMMAND_LINE_TARGETS else ''

if COMMAND == 'build':
    SConscript('scons/build.scons', exports={'env': env})

elif COMMAND == 'clean':
    AlwaysBuild(Command('#/clean', [], 'rm -rf build/*'))

elif COMMAND == 'format' or COMMAND == 'lint':
    SConscript('scons/format_lint.scons', exports={'env': env})

else: # Unknown command
    SConscript('scons/build.scons', exports={'env': env})

Help("build", "Build the project") 
Help("clean", "Clean build artifacts")
Help("format", "Format the code")
Help("lint", "Lint the code")
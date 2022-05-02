project('flashcards', 'c')

gtkdep = dependency('gtk4')
libadwaitadep = dependency('libadwaita-1')
sqlitedep = dependency('sqlite3')

gnome = import('gnome')
cc = meson.get_compiler('c')
common_cflags = cc.get_supported_arguments()

flashcards_resources = gnome.compile_resources('flashcards_resources',
  'flashcards.gresource.xml',
  source_dir: '.'
)

flashcards_schemas = gnome.compile_schemas()

executable('flashcards',
  'main.c',
  'flashcardsapp.c',
  'flashcardsappwin.c',
  'database.c',
  flashcards_resources,
  flashcards_schemas,
  dependencies: [gtkdep, libadwaitadep, sqlitedep],
  c_args: common_cflags
)

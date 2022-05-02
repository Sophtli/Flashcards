project('flashcards', 'c', version : '1.0.0', license : 'GPL')

gtk_dep = dependency('gtk4')
libadwaita_dep = dependency('libadwaita-1')
sqlite_dep = dependency('sqlite3')

gnome = import('gnome')
cc = meson.get_compiler('c')

subdir('src')
subdir('resources')

executable('flashcards',
  sourcefiles,
  resources,
  schemas,
  dependencies: [gtk_dep, libadwaita_dep, sqlite_dep]
)
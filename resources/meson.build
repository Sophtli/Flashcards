blueprints = custom_target('blueprints',
  input: files(
    'window.blp'
  ),
  output: '.',
  command: [find_program('blueprint-compiler'), 'batch-compile', '@OUTPUT@', '@CURRENT_SOURCE_DIR@', '@INPUT@'],
)

resources = gnome.compile_resources('resources',
  'flashcards.gresource.xml',
  dependencies: blueprints,
  c_name: 'flashcards'
)

schemas = gnome.compile_schemas()
# QMK Userspace

Welcome to my QMK userspace

This repository provides a custom firmware for my keyboard [Splitkb Aurora Corne rev1](https://github.com/splitkb/qmk_firmware/blob/elora/keyboards/splitkb/aurora/corne/readme.md)

## Quick setup

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Setup the userpace directory
```
cd $HOME
git clone git@github.com:Yokann/qmk_userspace.git
cd qmk_userspace
qmk config user.overlay_dir="$(realpath .)"
```
You should be able to compile normally using 
```
qmk compile -kb <my_keyboard> -km <my_keymap>
# or 
make <your_keyboard>:<your_keymap>
```

### Compile for a particular chip
```
# Example for liatris chip
qmk compile ... -e CONVERT_TO=liatris 
```

## Howto configure your build targets

1. Fork this repository
1. Clone your fork to your local machine
1. Add a new keymap for your board using `qmk new-keymap`
    * This will create a new keymap in the `keyboards` directory, in the same location that would normally be used in the main QMK repository. For example, if you wanted to add a keymap for the Planck, it will be created in `keyboards/planck/keymaps/<your keymap name>`
    * You can also create a new keymap using `qmk new-keymap -kb <your_keyboard> -km <your_keymap>`
    * Alternatively, add your keymap manually by placing it in the location specified above.
    * `layouts/<layout name>/<your keymap name>/keymap.*` is also supported if you prefer the layout system
1. Add your keymap(s) to the build by running `qmk userspace-add -kb <your_keyboard> -km <your_keymap>`
    * This will automatically update your `qmk.json` file
    * Corresponding `qmk userspace-remove -kb <your_keyboard> -km <your_keymap>` will delete it
    * Listing the build targets can be done with with `qmk userspace-list`
1. Commit your changes

## Documentation & Ressources

[QMK Configurator](https://config.qmk.fm/#/splitkb/aurora/corne/rev1/LAYOUT_split_3x6_3)


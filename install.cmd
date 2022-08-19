python -m pip install virtualenv
virtualenv env
env\Scripts\activate && python -m pip install cpplint && env\Scripts\deactivate && docker run --rm --name font-packer_installer -w C:\font-packer -v %CD%:C:\font-packer font-packer-custom-node ncu.cmd -u && npm.cmd install

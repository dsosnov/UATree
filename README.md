# pA16/UATree

For adding **UATree** (after *`git cms-init`*), from src directory:  
*`git submodule add https://github.com/dsosnov/UATree.git`*  
or  
*`git submodule add git@github.com:dsosnov/UATree.git`*  

*`scram b`*  

If **UADataFormat** has been changed, run:  
*`cd UATree/UADataFormat/; sh dictionary.sh; cd ../../`*  

Pushing from **UATree** directory:  
*`git push origin master`*  
For pushing you should add access token (using https for access) or ssh key (using ssh for access)  
Generate access token: https://help.github.com/articles/creating-an-access-token-for-command-line-use/  
Adding ssh key to github account: https://help.github.com/articles/connecting-to-github-with-ssh/  

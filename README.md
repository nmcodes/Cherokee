# Cherokee

## Seting up dev environment

### Install

```
    sudo apt-get update
    sudo apt-get install -y build-essential gcc
    git clone git@rendu-git.etna-alternance.net:module-6452/activity-36134/group-763776.git
```

### Compiling

```
    make
```

### Running

```
    ./Cherokee
```

## Workflow

### Feature

##### Create a branch for your work
```
    git checkout master // or the branch where you starting from
    git fetch master
    git checkout -b features/[FEATURE NAME]
```

##### Adding and commiting work on your branch
```
    git add file1.c file2.c ...
    git commit -m "[CHANGES YOU'VE MADE]"
    git push origin features/[FEATURE NAME]
```

##### After your work is done

- Synchronize with master with `git rebase -i master` or `git pull origin master`
- Go to https://rendu-git.etna-alternance.net/module-5002/activity-26897/group-678512
- Create a pull request on master
- Describe what you've made and **how to test it**

##### As a reviewer

- Pull the feature branch
- Test it as described in the PR comment
- If it seems ok to you
- Do not hesitate to comment the PR to ask something about the implementation, if you didn't understand something
- Mark the PR as approved
- If your not sure at 100% about the work, ask (on fb/slack...) to someone else to review it too
- Else Merge it

# CS246 Final Group Project - Chess

## Local Environment Setup

Jump to:

1. [Configure local git environment and generate an SSH key](#configure-local-git-environment-and-generate-an-ssh-key)
1. [Link your github account with yout local repository](#link-your-github-account-with-yout-local-repository)
1. [Clone the repository to local directory](#clone-the-repository-to-local-directory)
1. [Update the project and push your work](#update-the-project-and-push-your-work)


### Configure local git environment and generate an SSH key

1. Make sure git have been installed locally. 

2. Enter the local repository where you want the project to be stored at

```bash
cd project
```

3. initialize git in the current directory

```bash
git init
```

4. configure the local git with your name and email

```bash
git config user.name "Your github ID"
git config user.email "Your github email"
```

5. generate your local SSH key

```bash
ssh-keygen -t rsa -C "Your github email"
```

It will ask you to provide the file to store the keys. We want to store locally, so just type

```bash
id_rsa
```

Then, it will also provide a few options. We can just press enter to skip those

Make sure you have generated the id_rsa and id_rsa.pub file before the next step


### Link your github account with yout local repository

1. Open id_rsa.pub. It should only contain one line of key (start with ssh-rsa), and a new line. Copy the first line.

1. In github, go to Settings -> SSH and GPG keys. Click "New SSH key".
Name the title you want to call this key, paste the key, and then click "Add SSH key"


### Clone the repository to local directory

At the same directory that you configured git, clone the remote repository

```bash
git clone git@github.com:MidVC/CS246Chess.git
```

This should clone the remote repository to your local directory, and you can start coding!


### Update the project and push your work

Before each time you start working on the project, make sure you update the project first

```bash
git pull
```

This should update the project, normally without merge issues


If you finished one job, you can update your work to the remote github repository
You do this by:

1. add your changes on your local git

```bash
git add all_the_files_you_modified
```

2. commit your changes on your local git

```bash
git commit -m "describe what changes you make, briefly (normally about 10 words)"
```

3. push your changes to the github repository

```bash
git push
```

Now, if you successfully pushed your changes, you can see your commit on the github repository!

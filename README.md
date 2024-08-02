

# C++ Group Project

Welcome to the C++ Group Project! This guide will help you get started with collaborating on this project using Git. If you are new to Git, don't worry; we've got you covered.

## Table of Contents

- [Getting Started](#getting-started)
- [Cloning the Repository](#cloning-the-repository)
- [Working on a Branch](#working-on-a-branch)
- [Making Changes](#making-changes)
- [Syncing with the Remote Repository](#syncing-with-the-remote-repository)
- [Merging Changes](#merging-changes)
- [Additional Resources](#additional-resources)

## Getting Started

Before you begin, make sure you have Git installed on your computer. You can download Git from [git-scm.com](https://git-scm.com/).

## Cloning the Repository

To start working on the project, you need to clone the repository to your local machine. Open your terminal and run the following command:

```sh
git clone https://github.com/yourusername/your-repo-name.git
```

Replace `https://github.com/yourusername/your-repo-name.git` with the URL of the repository.

## Working on a Branch

To avoid conflicts and keep the main branch stable, always create a new branch for your changes. Follow these steps:

1. **Create a new branch:**

```sh
git checkout -b <branch-name>
```

Replace `<branch-name>` with a descriptive name for your branch (e.g., `feature-login`, `bugfix-header`).

2. **Switch to an existing branch:**

```sh
git checkout <branch-name>
```

## Making Changes

After making your changes, follow these steps to commit and push them:

1. **Stage your changes:**

```sh
git add .
```

2. **Commit your changes:**

```sh
git commit -m "Describe your changes here"
```

3. **Push your changes to the remote repository:**

```sh
git push -u origin <branch-name>
```

## Syncing with the Remote Repository

Before you start working, always make sure your local repository is up-to-date with the remote repository:

1. **Fetch the latest changes:**

```sh
git fetch origin
```

2. **Merge the latest changes into your branch:**

```sh
git merge origin/main
```

3. **Alternatively, you can pull the latest changes directly:**

```sh
git pull origin main
```

## Merging Changes

Once your changes are ready and reviewed, you can merge your branch into the `main` branch:

1. **Switch to the `main` branch:**

```sh
git checkout main
```

2. **Merge your branch into `main`:**

```sh
git merge <branch-name>
```

3. **Push the updated `main` branch to the remote repository:**

```sh
git push origin main
```

## Additional Resources

- [Git Documentation](https://git-scm.com/doc)
- [GitHub Guides](https://guides.github.com/)
- [Pro Git Book](https://git-scm.com/book/en/v2)


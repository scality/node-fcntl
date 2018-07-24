{
    'targets': [
        {
            'target_name': 'fcntl',
            'sources': [ 'src/fcntl.cpp' ],
            'include_dirs': [
                '<!(node -e "require(\'nan\')")'
            ]
        }
    ]
}

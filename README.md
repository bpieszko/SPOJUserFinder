# SPOJ User Finder
Script to look for people on Polish SPOJ Ranking.

## Making
```
g++-7 --std=c++17 -o SPOJUserFinder SPOJUserFinder.cpp -lcurl
```

## Usage
```
./SPOJUserFinder "user_name_visible_in_ranking"
```

## Example usage
```
./SPOJUserFinder "Bartosz Pieszko"
```

## Example result
```
Found Bartosz Pieszko on position 50
```

## Author
Bartosz Pieszko<br/>
bartosz.pieszko@gmail.com

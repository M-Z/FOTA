import { Injectable } from '@angular/core';
import { Resolve, ActivatedRouteSnapshot, RouterStateSnapshot } from '@angular/router';
import { paths } from 'app/app-paths';

@Injectable({
  providedIn: 'root'
})
export class PathResolveService implements Resolve<string | null> {

  resolve(
    route: ActivatedRouteSnapshot,
    state: RouterStateSnapshot
  ): string | null {

    // Detect is typo is way too far from guesses
    const typoPath = state.url.replace('/', '');
    const dictionary = Object.values(paths);

    // Sort the similarities from nearest to farthest
    this.sortByDistances(typoPath, dictionary);

    return `/${dictionary[0]}`;
  }

  getThreshold(path: string): number {
    return (path.length < 5) ? 3 : 5;
  }

  jaro_winkler(s1: string, s2: string): number {
    let m = 0;
    let i: number;
    let j: number;

    // Exit early if either are empty.
    if (s1.length === 0 || s2.length === 0) {
      return 0;
    }

    // case-insensitive
    s1 = s1.toUpperCase();
    s2 = s2.toUpperCase();

    // Exit early if they're an exact match.
    if (s1 === s2) {
      return 1;
    }

    const range = (Math.floor(Math.max(s1.length, s2.length) / 2)) - 1;
    const s1Matches = new Array(s1.length);
    const s2Matches = new Array(s2.length);

    for (i = 0; i < s1.length; i++) {
      const low = (i >= range) ? i - range : 0;
      const high = (i + range <= (s2.length - 1)) ? (i + range) : (s2.length - 1);

      for (j = low; j <= high; j++) {
        if (s1Matches[i] !== true && s2Matches[j] !== true && s1[i] === s2[j]) {
          ++m;
          s1Matches[i] = s2Matches[j] = true;
          break;
        }
      }
    }

    // Exit early if no matches were found.
    if (m === 0) {
      return 0;
    }

    // Count the transpositions.
    let k = 0;
    let numTrans = 0;

    for (i = 0; i < s1.length; i++) {
      if (s1Matches[i] === true) {
        for (j = k; j < s2.length; j++) {
          if (s2Matches[j] === true) {
            k = j + 1;
            break;
          }
        }

        if (s1[i] !== s2[j]) {
          ++numTrans;
        }
      }
    }

    let weight = (m / s1.length + m / s2.length + (m - (numTrans / 2)) / m) / 3;
    let l = 0;
    const p = 0.1;

    if (weight > 0.7) {
      while (s1[l] === s2[l] && l < 4) {
        ++l;
      }

      weight = weight + l * p * (1 - weight);
    }

    return weight;
  }

  sortByDistances(typoPath: string, dictionary: string[]) {
    const pathsDistance = {} as { [name: string]: number };

    dictionary.sort((a, b) => {
      if (!(a in pathsDistance)) {
        pathsDistance[a] = this.jaro_winkler(a, typoPath);
      }
      if (!(b in pathsDistance)) {
        pathsDistance[b] = this.jaro_winkler(b, typoPath);
      }

      return pathsDistance[b] - pathsDistance[a];
    });

  }
}

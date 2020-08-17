import { trigger, transition, style, animateChild, animate, query, group } from '@angular/animations';
import { paths } from 'app/app-paths';

const toRight = [
  style({ position: 'relative' }),
  query(':enter, :leave', [
    style({
      position: 'absolute',
      top: 0,
      left: 0,
      width: '100%',
      height: '100%'
    })
  ], { optional: true }),
  query(':enter', [
    style({ left: '-100%' })
  ], { optional: true }),
  query(':leave', animateChild(), { optional: true }),
  group([
    query(':leave', [
      animate('300ms ease-out', style({ left: '100%' }))
    ], { optional: true }),
    query(':enter', [
      animate('300ms ease-out', style({ left: '0%' }))
    ], { optional: true })
  ]),
  query(':enter', animateChild()),
];

const toLeft = [
  style({ position: 'relative' }),
  query(':enter, :leave', [
    style({
      position: 'absolute',
      top: 0,
      left: 0,
      width: '100%',
      height: '100%'
    })
  ], { optional: true }),
  query(':enter', [
    style({ left: '200%' })
  ], { optional: true }),
  query(':leave', animateChild(), { optional: true }),
  group([ // Execute at the same time
    query(':leave', [
      animate('300ms ease-out', style({ left: '-100%' }))
    ], { optional: true }),
    query(':enter', [
      animate('300ms ease-out', style({ left: '0%' }))
    ], { optional: true })
  ]),
  query(':enter', animateChild(), { optional: true }),
];

const fadeInOut = [
  query(':enter, :leave',
    style({
      position: 'absolute',
      width: '100%',
      height: '100%',
      opacity: 1
    })
  ),
  group([
    query(':enter', [
      style({ opacity: 0 }),
      animate('800ms ease-in-out', style({ opacity: 1 }))
    ]),
    query(':leave', [
      style({ opacity: 1 }),
      animate('500ms ease-in-out', style({ opacity: 0 }))
    ], { optional: true }),
  ])
];

export const routeAnimations =
  trigger('routeAnimations', [

    // Going from left to right nav
    transition(paths.Home + '=> *', toLeft),
    transition('* =>' + paths.Upload, toLeft),
    transition(paths.Terminal + '=>' + paths.Stats, toLeft),

    // Right to left nav
    transition(paths.Upload + '=> *', toRight),
    transition('* =>' + paths.Home, toRight),
    transition(paths.Stats + '=>' + paths.Terminal, toRight),

    transition('* =>' + paths.NotFound, fadeInOut)
  ]);

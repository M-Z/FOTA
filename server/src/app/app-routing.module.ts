import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { paths } from './app-paths';
import { PathResolveService } from './core/services/Path-Resolve/path-resolve.service';
import { AuthGuard } from './core/guards/Auth/auth.guard';
import { Role } from './shared/models/role.model';

const routes: Routes = [{
  path: '',
  redirectTo: paths.Home,
  pathMatch: 'full',
}, {
  path: paths.Home,
  loadChildren: () => import('./modules/home/home.module').then(m => m.HomeModule),
  data: {
    title: paths.Home,
    animation: paths.Home
  }
}, {
  path: paths.Team,
  loadChildren: () => import('./modules/teams/teams.module').then(m => m.TeamsModule),
  canActivate: [AuthGuard],
  data: {
    title: paths.Team,
    animation: paths.Team,
    roles: [Role.Admin, Role.Leader, Role.Developer]
  }
}, {
  path: paths.Terminal,
  loadChildren: () => import('./modules/terminal/terminal.module').then(m => m.TerminalModule),
  canActivate: [AuthGuard],
  data: {
    title: paths.Terminal,
    animation: paths.Terminal,
    roles: [Role.Admin, Role.Leader]
  }
}, {
  path: paths.Stats,
  loadChildren: () => import('./modules/stats/stats.module').then(m => m.StatsModule),
  canActivate: [AuthGuard],
  data: {
    title: paths.Stats,
    animation: paths.Stats,
    roles: [Role.Admin, Role.Leader]
  }
}, {
  path: paths.Upload,
  loadChildren: () => import('./modules/upload/upload.module').then(m => m.UploadModule),
  canActivate: [AuthGuard],
  data: {
    title: paths.Upload,
    animation: paths.Upload,
    roles: [Role.Developer, Role.Leader]
  }
}, {
  path: paths.Login,
  loadChildren: () => import('./modules/login/login.module').then(m => m.LoginModule),
  canActivate: [AuthGuard],
  data: {
    title: paths.Login,
    animation: paths.Login,
    roles: [Role.Guest]
  }
}, {
  path: 'register',
  loadChildren: () => import('./modules/register/register.module').then(m => m.RegisterModule),
  canActivate: [AuthGuard],
  data: {
    title: 'Welcome',
    roles: [Role.Guest]
  }
}, {
  path: '**',
  loadChildren: () => import('./modules/not-found/not-found.module').then(m => m.NotFoundModule),
  resolve: {
    path: PathResolveService
  },
  data: {
    title: 'Not Found',
    animation: 'NotFound'
  }
}];

@NgModule({
  imports: [
    RouterModule.forRoot(routes)
  ],
  exports: [
    RouterModule
  ]
})

export class AppRoutingModule { }

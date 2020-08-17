import { CommonModule } from '@angular/common';

import { NgModule } from '@angular/core';
import { RouterModule } from '@angular/router';
import { HttpClientModule, HTTP_INTERCEPTORS } from '@angular/common/http'

import { SharedModule } from 'app/shared/shared.module';

import { ErrorIntercept } from './interceptors/ErrorHttp/error-http.interceptor';
import { LoaderInterceptor } from './interceptors/Loader/loader.interceptor';
import { AuthInterceptor } from './interceptors/Auth/auth.interceptor';

import { TransitionScreenComponent } from './transition-screen/transition-screen.component';
import { HeaderComponent } from './header/header.component';
import { FooterComponent } from './footer/footer.component';

@NgModule({
  declarations: [
    HeaderComponent,
    FooterComponent,
    TransitionScreenComponent
  ],
  exports: [
    HeaderComponent,
    FooterComponent,
    TransitionScreenComponent
  ],
  imports: [
    CommonModule,
    SharedModule,  // DatePipe for FooterComponent, show-errors component
    RouterModule,   // For HeaderComponent
    HttpClientModule
  ],
  providers: [
    {
      provide: HTTP_INTERCEPTORS,
      useClass: AuthInterceptor,
      multi: true
    }, {
      provide: HTTP_INTERCEPTORS,
      useClass: ErrorIntercept,
      multi: true
    }, {
      provide: HTTP_INTERCEPTORS,
      useClass: LoaderInterceptor,
      multi: true
    }]
})
export class CoreModule { }

import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

import { NgModule } from '@angular/core';

import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';

import { CoreModule } from './core/core.module';

@NgModule({
  imports: [
    AppRoutingModule,
    BrowserModule,
    BrowserAnimationsModule,  // Must be imported with BrowserModule
    HttpClientModule,
    FormsModule,
    CoreModule
  ],
  declarations: [
    AppComponent
  ],
  providers: [
    CoreModule
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }

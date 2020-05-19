import { Injectable } from '@angular/core';

interface Script {
  type: string;
  name: string;
  src?: string;
  link?: string;
  integrity?: string;
}

export const ScriptStore: Script[] = [{
  type: 'style',
  name: 'bootstrap',
  link: 'https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css',
  integrity: 'sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T'
}, {
  type: 'style',
  name: 'styles',
  link: '/assets/scss/styles.min.css'
}];

@Injectable({
  providedIn: 'root'
})
export class ScriptStoreService {

  private scripts: {
    data: Script;
    loaded: boolean;
  }[] = [];

  constructor() {
    ScriptStore.forEach((script: Script) => {
      this.scripts[script.name] = {
        data: script,
        loaded: false
      };
    });
  }

  load(...scripts: string[]) {
    const promises: any[] = [];
    scripts.forEach((script) => promises.push(this.loadFile(script)));
    return Promise.all(promises);
  }

  loadFile(name: string) {
    return new Promise((resolve, reject) => {

      // resolve if already loaded
      if (this.scripts[name].loaded) {
        resolve({
          script: name,
          loaded: true,
          status: 'Already Loaded'
        });
      }

      let l: HTMLScriptElement | HTMLLinkElement;
      switch (this.scripts[name].data.type) {
        case 'script':
          l = document.createElement('script')
          l.src = this.scripts[name].data.src;
          l.type = 'text/javascript';

          if (this.scripts[name].data.integrity) {
            l.integrity = this.scripts[name].data.integrity;
          }
          document.body.appendChild(l);
          break;
        case 'style':
          l = document.createElement('link');
          l.rel = 'stylesheet';
          l.href = this.scripts[name].data.link;

          if (this.scripts[name].data.integrity) {
            l.integrity = this.scripts[name].data.integrity;
            l.crossOrigin = "anonymous";
          }

          document.head.appendChild(l);
          break;
      }

      l.onerror = () => resolve({
        script: name,
        loaded: false,
        status: 'Loaded'
      });

      const resolved = () => {
        l.removeEventListener('load', resolved);
        this.scripts[name].loaded = true;
        console.log(`${name} Loaded.`);
        resolve({
          script: name,
          loaded: true,
          status: 'Loaded'
        });
      }

      // wait for the file to finish loading
      l.addEventListener('load', resolved);
    });
  }

}

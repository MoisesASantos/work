"use client"

import { useState, useEffect } from "react"
import Link from "next/link"
import { useSearchParams, useRouter } from "next/navigation"
import { motion, AnimatePresence } from "framer-motion"
import { Pill, ArrowLeft, Mail, Lock, Eye, EyeOff, Phone } from "lucide-react"

const AUTH_KEY = "apothecary_auth"

export default function LoginPage() {
  const searchParams = useSearchParams()
  const router = useRouter()
  
  const initialTab = searchParams.get('tab') === 'register' ? 'register' : 'login'
  const redirectUrl = searchParams.get('redirect') || '/pesquisa'
  const safeRedirectUrl = redirectUrl.startsWith('/') ? redirectUrl : '/pesquisa'
  
  const [activeTab, setActiveTab] = useState<'login' | 'register'>(initialTab)
  const [showPassword, setShowPassword] = useState(false)
  
  // Update internal state if the URL search parameter changes
  useEffect(() => {
    setActiveTab(searchParams.get('tab') === 'register' ? 'register' : 'login')
  }, [searchParams])

  const authenticateAndRedirect = () => {
    localStorage.setItem(AUTH_KEY, "true")
    router.push(safeRedirectUrl)
  }

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault()
    authenticateAndRedirect()
  }

  return (
    <div className="min-h-screen bg-background flex flex-col md:flex-row relative">
      
      {/* ── Left Decorative Section (hidden on small screens) ── */}
      <div className="hidden relative md:flex md:w-1/2 bg-slate-950 text-white overflow-hidden items-center justify-center p-12 z-0">
        <div className="absolute inset-0 pointer-events-none">
          <div className="absolute top-[-10%] right-[-10%] w-[500px] h-[500px] bg-primary/20 rounded-full blur-[100px]" />
          <div className="absolute bottom-[-10%] left-[-10%] w-[400px] h-[400px] bg-blue-500/20 rounded-full blur-[100px]" />
          <div className="absolute inset-0 bg-[linear-gradient(to_right,#ffffff05_1px,transparent_1px),linear-gradient(to_bottom,#ffffff05_1px,transparent_1px)] bg-[size:32px_32px]" />
        </div>

        <div className="relative z-10 max-w-lg">
          <Link href="/landing" className="inline-flex items-center gap-2 text-2xl font-bold font-serif text-primary hover:opacity-80 transition-opacity mb-12">
            <Pill className="w-8 h-8" />
            Apothecary
          </Link>
          <h1 className="text-4xl lg:text-5xl font-black mb-6 leading-[1.1]">
            A sua saúde, <br />
            <span className="text-primary italic font-serif opacity-90">mais conectada</span>.
          </h1>
          <p className="text-lg text-white/70 leading-relaxed">
            Aceda à maior rede digital de saúde em Angola. Compare preços, reserve medicamentos e consulte o nosso guia de sintomas de forma rápida e 100% segura.
          </p>
          
          <div className="mt-12 grid grid-cols-2 gap-6">
            <div className="p-5 border border-white/10 rounded-2xl bg-white/5 backdrop-blur-sm">
              <div className="text-primary text-2xl font-black mb-1">5k+</div>
              <div className="text-xs text-white/60 uppercase font-bold tracking-wider">Produtos</div>
            </div>
            <div className="p-5 border border-white/10 rounded-2xl bg-white/5 backdrop-blur-sm">
              <div className="text-primary text-2xl font-black mb-1">200+</div>
              <div className="text-xs text-white/60 uppercase font-bold tracking-wider">Clínicas</div>
            </div>
          </div>
        </div>
      </div>

      {/* ── Right Form Section ── */}
      <div className="w-full md:w-1/2 min-h-screen flex flex-col pt-8 pb-12 px-6 md:px-12 lg:px-24 items-center justify-center relative z-10 bg-background overflow-y-auto">
        <div className="w-full max-w-md">
          {/* Mobile Back Button & Logo */}
          <div className="w-full flex justify-between items-center mb-12 md:hidden">
            <Link href="/landing" className="p-2 -ml-2 rounded-full hover:bg-muted text-muted-foreground transition-colors">
              <ArrowLeft className="w-6 h-6" />
            </Link>
            <Link href="/landing" className="flex items-center gap-2 text-xl font-bold font-serif text-primary">
              <Pill className="w-6 h-6" />
              Apothecary
            </Link>
          </div>

          {/* Desktop Back Button */}
          <Link href="/landing" className="hidden md:inline-flex items-center gap-2 text-sm text-muted-foreground hover:text-foreground font-medium mb-12 transition-colors">
            <ArrowLeft className="w-4 h-4" /> Voltar ao Início
          </Link>

          {/* Tabs Container */}
          <div className="bg-muted p-1.5 rounded-[1.25rem] flex w-full mb-8 relative">
            {/* Animated Tab Indicator */}
            <motion.div 
              layoutId="auth-tab-indicator"
              className="absolute top-1.5 bottom-1.5 w-[calc(50%-6px)] bg-background rounded-xl shadow-sm border border-border/50"
              initial={false}
              animate={{
                left: activeTab === 'login' ? '6px' : 'calc(50%)',
              }}
              transition={{ type: "spring", stiffness: 400, damping: 30 }}
            />
            
            <button
              onClick={() => setActiveTab('login')}
              className={`flex-1 relative z-10 py-3 text-sm font-bold transition-colors rounded-xl ${activeTab === 'login' ? 'text-foreground' : 'text-muted-foreground hover:text-foreground'}`}
            >
              Entrar
            </button>
            <button
              onClick={() => setActiveTab('register')}
              className={`flex-1 relative z-10 py-3 text-sm font-bold transition-colors rounded-xl ${activeTab === 'register' ? 'text-foreground' : 'text-muted-foreground hover:text-foreground'}`}
            >
              Criar Conta
            </button>
          </div>

          {/* Form Area */}
          <div className="relative">
            <AnimatePresence mode="wait">
              {activeTab === 'login' ? (
                <motion.div
                  key="login"
                  initial={{ opacity: 0, x: -20 }} animate={{ opacity: 1, x: 0 }} exit={{ opacity: 0, x: -20 }} transition={{ duration: 0.2 }}
                  className="space-y-6"
                >
                  <div className="space-y-2 mb-8">
                    <h2 className="text-3xl font-black text-foreground">Bem-vindo de volta!</h2>
                    <p className="text-muted-foreground text-sm">Insira as suas credenciais para aceder à sua conta.</p>
                  </div>

                  <form className="space-y-4" onSubmit={handleSubmit}>
                    <div className="space-y-1.5">
                      <label className="text-sm font-semibold text-foreground/80 pl-1">Email ou N.º de Telefone</label>
                      <div className="relative">
                        <div className="absolute inset-y-0 left-0 pl-4 flex items-center pointer-events-none text-muted-foreground">
                          <Mail className="w-5 h-5 opacity-60" />
                        </div>
                        <input 
                          type="text" 
                          placeholder="exemplo@gmail.com ou 9XX..." 
                          className="w-full bg-card border border-border focus:border-primary/50 focus:ring-4 focus:ring-primary/10 rounded-xl py-3.5 pl-12 pr-4 outline-none transition-all text-sm"
                        />
                      </div>
                    </div>

                    <div className="space-y-1.5">
                      <div className="flex items-center justify-between pl-1">
                        <label className="text-sm font-semibold text-foreground/80">Palavra-passe</label>
                        <a href="#" className="text-xs font-bold text-primary hover:underline">Esqueceu-se?</a>
                      </div>
                      <div className="relative">
                        <div className="absolute inset-y-0 left-0 pl-4 flex items-center pointer-events-none text-muted-foreground">
                          <Lock className="w-5 h-5 opacity-60" />
                        </div>
                        <input 
                          type={showPassword ? "text" : "password"} 
                          placeholder="••••••••" 
                          className="w-full bg-card border border-border focus:border-primary/50 focus:ring-4 focus:ring-primary/10 rounded-xl py-3.5 pl-12 pr-12 outline-none transition-all text-sm font-mono tracking-wider"
                        />
                        <button 
                          type="button"
                          onClick={() => setShowPassword(!showPassword)}
                          className="absolute inset-y-0 right-0 pr-4 flex items-center text-muted-foreground hover:text-foreground transition-colors"
                        >
                          {showPassword ? <EyeOff className="w-5 h-5 opacity-60" /> : <Eye className="w-5 h-5 opacity-60" />}
                        </button>
                      </div>
                    </div>

                    <button 
                      type="submit" 
                      className="w-full bg-primary text-primary-foreground font-bold py-4 rounded-xl mt-2 shadow-lg hover:shadow-primary/30 hover:-translate-y-0.5 transition-all"
                    >
                      Aceder à Conta
                    </button>
                  </form>
                </motion.div>
              ) : (
                <motion.div
                  key="register"
                  initial={{ opacity: 0, x: 20 }} animate={{ opacity: 1, x: 0 }} exit={{ opacity: 0, x: 20 }} transition={{ duration: 0.2 }}
                  className="space-y-6"
                >
                  <div className="space-y-2 mb-8">
                    <h2 className="text-3xl font-black text-foreground">Junte-se a nós.</h2>
                    <p className="text-muted-foreground text-sm">Crie a sua conta e aceda a centenas de farmácias num só lugar.</p>
                  </div>

                  <form className="space-y-4" onSubmit={handleSubmit}>
                    <div className="space-y-1.5">
                      <label className="text-sm font-semibold text-foreground/80 pl-1">Email ou N.º de Telefone</label>
                      <div className="relative">
                        <div className="absolute inset-y-0 left-0 pl-4 flex items-center pointer-events-none text-muted-foreground">
                          <Mail className="w-5 h-5 opacity-60" />
                        </div>
                        <input 
                          type="text" 
                          placeholder="Informe seu email ou telemóvel" 
                          className="w-full bg-card border border-border focus:border-primary/50 focus:ring-4 focus:ring-primary/10 rounded-xl py-3.5 pl-12 pr-4 outline-none transition-all text-sm"
                        />
                      </div>
                    </div>

                    <div className="space-y-1.5">
                      <label className="text-sm font-semibold text-foreground/80 pl-1">Palavra-passe</label>
                      <div className="relative">
                        <div className="absolute inset-y-0 left-0 pl-4 flex items-center pointer-events-none text-muted-foreground">
                          <Lock className="w-5 h-5 opacity-60" />
                        </div>
                        <input 
                          type={showPassword ? "text" : "password"} 
                          placeholder="No mínimo 8 caracteres" 
                          className="w-full bg-card border border-border focus:border-primary/50 focus:ring-4 focus:ring-primary/10 rounded-xl py-3.5 pl-12 pr-12 outline-none transition-all text-sm font-mono tracking-wider"
                        />
                        <button 
                          type="button"
                          onClick={() => setShowPassword(!showPassword)}
                          className="absolute inset-y-0 right-0 pr-4 flex items-center text-muted-foreground hover:text-foreground transition-colors"
                        >
                          {showPassword ? <EyeOff className="w-5 h-5 opacity-60" /> : <Eye className="w-5 h-5 opacity-60" />}
                        </button>
                      </div>
                    </div>

                    <div className="pt-2">
                       <label className="flex items-start gap-3 p-1 cursor-pointer group">
                         <div className="relative flex items-center pt-0.5">
                           <input type="checkbox" className="w-4 h-4 rounded text-primary border-border focus:ring-primary/20 cursor-pointer" />
                         </div>
                         <span className="text-xs text-muted-foreground font-medium leading-relaxed group-hover:text-foreground transition-colors">
                           Aceito os <a href="#" className="font-bold text-primary hover:underline">Termos de Serviço</a> e a <a href="#" className="font-bold text-primary hover:underline">Política de Privacidade</a>.
                         </span>
                       </label>
                    </div>

                    <button 
                      type="submit" 
                      className="w-full bg-primary text-primary-foreground font-bold py-4 rounded-xl mt-2 shadow-lg hover:shadow-primary/30 hover:-translate-y-0.5 transition-all"
                    >
                      Concluir Registo
                    </button>
                  </form>
                </motion.div>
              )}
            </AnimatePresence>
          </div>

          <div className="mt-10 relative">
            <div className="absolute inset-0 flex items-center">
              <div className="w-full border-t border-border"></div>
            </div>
            <div className="relative flex justify-center text-sm">
              <span className="px-4 bg-background text-muted-foreground font-medium">Ou continuar com</span>
            </div>
          </div>

          <div className="mt-8 space-y-3">
            <button
              onClick={authenticateAndRedirect}
              className="relative w-full flex items-center justify-center gap-3 bg-card border border-border/70 hover:border-border hover:bg-muted py-3.5 rounded-xl font-bold text-foreground transition-all hover:shadow-sm"
            >
              <img src="https://www.svgrepo.com/show/475656/google-color.svg" alt="Google" className="w-5 h-5" />
              Conta Google
            </button>
          </div>
          
        </div>
      </div>
      
    </div>
  )
}

"use client"

import { useState } from "react"
import Link from "next/link"
import { MapPin, Bell, Menu, CheckCircle2, Pill, FileText } from "lucide-react"
import Image from "next/image"
import { Sheet, SheetContent, SheetTrigger, SheetTitle, SheetDescription } from "@/components/ui/sheet"
import { SidebarContent } from "@/components/layout/sidebar"
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuLabel,
  DropdownMenuSeparator,
  DropdownMenuTrigger,
} from "@/components/ui/dropdown-menu"

// Mock notifications data
const initialNotifications = [
  {
    id: 1,
    title: "Hora do Medicamento",
    description: "Tomar 1 comprimido de Paracetamol 500mg.",
    time: "Agora",
    read: false,
    icon: Pill,
    color: "text-blue-500",
    bg: "bg-blue-50 dark:bg-blue-500/10",
  },
  {
    id: 2,
    title: "Medicamento em Stock",
    description: "A Amoxicilina que procurava está disponível na Apothecary Maianga.",
    time: "Há 2 horas",
    read: false,
    icon: CheckCircle2,
    color: "text-green-500",
    bg: "bg-green-50 dark:bg-green-500/10",
  },
  {
    id: 3,
    title: "Receita Validada",
    description: "A sua receita foi analisada e os medicamentos identificados.",
    time: "Ontem",
    read: true,
    icon: FileText,
    color: "text-primary",
    bg: "bg-primary/10",
  },
]

export function TopNav() {
  const [open, setOpen] = useState(false)
  const [notifications, setNotifications] = useState(initialNotifications)

  const unreadCount = notifications.filter(n => !n.read).length

  const markAllAsRead = () => {
    setNotifications(notifications.map(n => ({ ...n, read: true })))
  }

  return (
    <header className="fixed top-0 right-0 left-0 md:left-64 z-40 bg-white/80 dark:bg-slate-900/80 backdrop-blur-xl border-b border-border/10 h-16 flex items-center justify-between px-4 md:px-6">
      {/* Mobile left side (Menu + Logo) */}
      <div className="flex items-center gap-3 md:hidden">
        <Sheet open={open} onOpenChange={setOpen}>
          <SheetTrigger asChild>
            <button className="p-2 -ml-2 text-foreground hover:bg-muted transition-all rounded-full flex items-center justify-center">
              <Menu className="w-5 h-5" />
            </button>
          </SheetTrigger>
          <SheetContent side="left" className="p-4 w-64 bg-slate-50 dark:bg-slate-950 flex flex-col pt-12">
            <SheetTitle className="sr-only">Menu de Navegação</SheetTitle>
            <SheetDescription className="sr-only">Navegue pelas páginas da aplicação pelas opções disponíveis.</SheetDescription>
            <div onClick={() => setOpen(false)} className="flex flex-col h-full">
              <SidebarContent />
            </div>
          </SheetContent>
        </Sheet>
        
        {/* Logo - Mobile only */}
        <span className="text-xl font-bold tracking-tight text-primary font-serif">
          Apothecary
        </span>
      </div>

      {/* Location - Desktop */}
      <button className="hidden md:flex items-center gap-2 px-3 py-2 text-foreground hover:bg-muted transition-all rounded-xl">
        <MapPin className="w-5 h-5 text-primary" />
        <div className="text-left">
          <p className="text-sm font-semibold">Luanda, Angola</p>
          <p className="text-xs text-muted-foreground">Talatona</p>
        </div>
      </button>

      {/* Right Actions */}
      <div className="flex items-center gap-3">
        {/* Location - Mobile */}
        <button className="md:hidden p-2 text-foreground hover:bg-muted transition-all rounded-full flex items-center gap-2">
          <MapPin className="w-5 h-5 text-primary" />
        </button>

        {/* Notifications */}
        <DropdownMenu>
          <DropdownMenuTrigger asChild>
            <button className="relative p-2.5 text-foreground hover:bg-muted transition-all rounded-full outline-none focus-visible:ring-2 focus-visible:ring-primary focus-visible:ring-offset-2">
              <Bell className="w-5 h-5" />
              {unreadCount > 0 && (
                <span className="absolute top-1.5 right-1.5 w-2.5 h-2.5 bg-destructive rounded-full border-2 border-white dark:border-slate-900" />
              )}
            </button>
          </DropdownMenuTrigger>
          <DropdownMenuContent align="end" className="w-80 md:w-96 p-0 rounded-2xl overflow-hidden shadow-xl border-border/10">
            <div className="flex items-center justify-between px-4 py-3 bg-muted/30 border-b border-border/5">
              <span className="font-bold font-serif text-foreground">Notificações</span>
              {unreadCount > 0 && (
                <button 
                  onClick={markAllAsRead}
                  className="text-xs text-primary font-semibold hover:underline"
                >
                  Marcar como lidas
                </button>
              )}
            </div>
            <div className="max-h-[300px] md:max-h-[400px] overflow-y-auto overflow-x-hidden p-2 space-y-1">
              {notifications.length > 0 ? (
                notifications.map((notification) => {
                  const Icon = notification.icon;
                  return (
                    <DropdownMenuItem 
                      key={notification.id}
                      className={`flex gap-3 items-start p-3 rounded-xl cursor-default focus:bg-muted outline-none transition-colors ${notification.read ? "opacity-70" : "bg-primary/5"}`}
                    >
                      <div className={`mt-0.5 w-10 h-10 rounded-full flex items-center justify-center flex-shrink-0 ${notification.bg}`}>
                        <Icon className={`w-5 h-5 ${notification.color}`} />
                      </div>
                      <div className="flex-1 space-y-1 overflow-hidden">
                        <div className="flex items-center justify-between gap-2">
                          <p className={`text-sm font-semibold truncate ${notification.read ? "text-foreground" : "text-primary"}`}>
                            {notification.title}
                          </p>
                          <span className="text-[10px] whitespace-nowrap text-muted-foreground font-medium">
                            {notification.time}
                          </span>
                        </div>
                        <p className="text-xs text-muted-foreground leading-snug line-clamp-2">
                          {notification.description}
                        </p>
                      </div>
                      {!notification.read && (
                        <div className="w-2 h-2 rounded-full bg-primary flex-shrink-0 mt-1.5" />
                      )}
                    </DropdownMenuItem>
                  )
                })
              ) : (
                <div className="p-8 text-center text-muted-foreground">
                  <Bell className="w-8 h-8 opacity-20 mx-auto mb-2" />
                  <p className="text-sm font-medium">Nenhuma notificação</p>
                </div>
              )}
            </div>
            <div className="p-3 border-t border-border/5 bg-muted/30 text-center">
              <button className="text-xs font-bold text-muted-foreground hover:text-foreground">
                Ver todas as notificações
              </button>
            </div>
          </DropdownMenuContent>
        </DropdownMenu>

        {/* Profile */}
        <Link href="/perfil" className="relative w-9 h-9 rounded-full bg-muted overflow-hidden ring-2 ring-primary/20 hover:ring-primary/40 transition-all">
          <Image
            src="https://images.unsplash.com/photo-1472099645785-5658abf4ff4e?w=100&h=100&fit=crop&crop=face"
            alt="Perfil do utilizador"
            fill
            priority
            className="object-cover"
          />
        </Link>
      </div>
    </header>
  )
}
